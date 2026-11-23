import polars as pl

keepData = [
    # Dataset filtering
    "play", "aborted_play", "play_deleted", "special", "qb_kneel", "qb_spike", "season_type",

    # Possible Target vars
    "play_type", "yards_gained", "first_down", "success",

    # Pre-snap filters
    "yardline_100", "down", "ydstogo", "goal_to_go", "qtr",
    "quarter_seconds_remaining", "half_seconds_remaining", "game_seconds_remaining",
    "score_differential", "posteam_timeouts_remaining", "defteam_timeouts_remaining",

    # Nice-to-have: Game Context
    "posteam_type", "div_game", "season", "week",

    # Nice-to-have: Environment
    "roof", "surface", "temp", "wind"
]

dropCols = [
    "play", "aborted_play", "play_deleted", "special", "qb_kneel", "qb_spike", "down"
]

clean = (
    pl.scan_csv(
        "pbp.csv",
        ignore_errors=True,
        null_values=["NA", ""],
        infer_schema_length=10000,
        schema_overrides={"play_deleted": pl.Float64},
    )
    .select(keepData)
    .filter(
        (pl.col("play") == 1) &
        (pl.col("aborted_play").fill_null(0) == 0) &
        (pl.col("play_deleted").fill_null(0) == 0) &
        (pl.col("season_type").is_in(["REG", "POST"])) &
        (pl.col("special").fill_null(0) == 0) &
        (pl.col("qb_kneel").fill_null(0) == 0) &
        (pl.col("qb_spike").fill_null(0) == 0) &
        (pl.col("play_type").is_in(["run", "pass"])) &
        (pl.col("down").is_not_null()) &
        (pl.col("qtr") <= 4)
    )
    # 1. Encode strings, fix goal_to_go nulls, and one-hot encode down
    .with_columns(
        (pl.col("season_type") == "POST").cast(pl.Float32),
        (pl.col("play_type") == "pass").cast(pl.Float32),
        (pl.col("posteam_type") == "home").cast(pl.Float32),
        pl.col("roof").is_in(["dome", "closed"]).fill_null(False).cast(pl.Float32),
        (pl.col("surface").str.strip_chars() == "grass").fill_null(False).cast(pl.Float32),
        pl.col("goal_to_go").fill_null(
            (pl.col("yardline_100") == pl.col("ydstogo")).cast(pl.Float32)
        ),
        (pl.col("down") == 1.0).cast(pl.Float32).alias("down_1"),
        (pl.col("down") == 2.0).cast(pl.Float32).alias("down_2"),
        (pl.col("down") == 3.0).cast(pl.Float32).alias("down_3"),
        (pl.col("down") == 4.0).cast(pl.Float32).alias("down_4"),
    )
    # 2. Impute temp/wind now that roof is 1.0 (indoors) / 0.0 (outdoors)
    .with_columns(
        pl.when(pl.col("roof") == 1.0)
          .then(70.0)
          .otherwise(pl.col("temp").cast(pl.Float32).fill_null(60.0))
          .alias("temp"),
        pl.when(pl.col("roof") == 1.0)
          .then(0.0)
          .otherwise(pl.col("wind").cast(pl.Float32).fill_null(7.0))
          .alias("wind"),
    )
    # 3. Drop constant filter cols + raw down, and cast everything to Float32
    .drop(dropCols)
    .select(pl.all().cast(pl.Float32))
    .collect()
)

assert clean.null_count().sum_horizontal().item() == 0, "Nulls remaining!"
print("Clean shape:", clean.shape)
clean.write_csv("pbpClean.csv")
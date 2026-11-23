import polars as pl

keepData = [
    # Dataset filtering
    "play", "aborted_play", "play_deleted", "special", "qb_kneel", "qb_spike", "season_type",

    # Possioble Target vars
    "play_type", "yards_gained", "first_down", "success",

    # Pre-snap filters
    "yardline_100", "down", "ydstogo", "goal_to_go", "qtr", "quarter_seconds_remaining", "half_seconds_remaining", "game_seconds_remaining", "score_differential", "posteam_timeouts_remaining", "defteam_timeouts_remaining",

    # Nice-to-have: Game Context
    "posteam_type", "div_game", "season", "week",

    # Nice-to-have: Pre-snap
    "shotgun", "no_huddle", "play_clock",

    # Nice-to-have: Market Lines
    "spread_line", "total_line",

    # Nice-to-have: Enviorment
    "roof", "surface", "temp", "wind"
]

clean = pl.scan_csv(
            "pbp.csv",
            ignore_errors=True,
            null_values=["NA", ""],
            infer_schema_length=10000,
            schema_overrides={"play_deleted": pl.Float64}, ).select(keepData).filter(
                (pl.col("play") == 1) &
                (pl.col("aborted_play") == 0) &
                (pl.col("play_deleted").fill_null(0) == 0) &
                (pl.col("special") == 0) &
                (pl.col("qb_kneel") == 0) &
                (pl.col("qb_spike") == 0) &
                (pl.col("season_type") == "REG") &
                (pl.col("play_type").is_in(["run", "pass"])) &
                (pl.col("down").is_not_null()) &
                (pl.col("qtr") <= 4)
        ).collect()

clean.write_csv("pbp.csv")
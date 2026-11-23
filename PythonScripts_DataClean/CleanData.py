import polars as pl

keepData = [
    # Dataset filtering
    "play", "aborted_play", "play_deleted", "special", "qb_kneel", "qb_spike", "season_type",

    # Target vars
    "play_type", "yards_gained", "first_down", "success",

    # Pre-snap game state
    "yardline_100", "down", "ydstogo", "goal_to_go", "qtr",
    "quarter_seconds_remaining", "half_seconds_remaining", "game_seconds_remaining",
    "score_differential", "posteam_timeouts_remaining", "defteam_timeouts_remaining",

    # Game context
    "posteam_type", "div_game", "season", "week",

    # Environment
    "roof", "surface", "temp", "wind"
]

dropCols = [
    "play", "aborted_play", "play_deleted", "special", "qb_kneel", "qb_spike", "down"
]

targetCols = ["yards_gained", "first_down", "success"]

# Step 1: Load raw CSV and keep only the columns we care about
clean = pl.scan_csv(
    "pbp.csv",
    ignore_errors=True,
    null_values=["NA", ""],
    infer_schema_length=10000,
    schema_overrides={"play_deleted": pl.Float64},
)
clean = clean.select(keepData)

# Step 2: Filter out non-plays, special teams, kneels, spikes, and OT
clean = clean.filter(
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

# Step 3: Turn text columns into 1.0 / 0.0
clean = clean.with_columns(
    (pl.col("season_type") == "POST").cast(pl.Float32),
    (pl.col("play_type") == "pass").cast(pl.Float32),
    (pl.col("posteam_type") == "home").cast(pl.Float32),
    pl.col("roof").is_in(["dome", "closed"]).fill_null(False).cast(pl.Float32),
    (pl.col("surface").str.strip_chars() == "grass").fill_null(False).cast(pl.Float32),
)

# Step 4: Fill missing values
# - goal_to_go: true when yards to endzone == yards to first down
# - temp/wind: indoor games get 70F / 0 mph; missing outdoor games get 60F / 7 mph
is_goal_to_go = (pl.col("yardline_100") == pl.col("ydstogo")).cast(pl.Float32)
is_indoors = pl.col("roof") == 1.0

clean = clean.with_columns(
    pl.col("goal_to_go").fill_null(is_goal_to_go),
    pl.when(is_indoors).then(70.0).otherwise(pl.col("temp").fill_null(60.0)).alias("temp"),
    pl.when(is_indoors).then(0.0).otherwise(pl.col("wind").fill_null(7.0)).alias("wind"),
)

# Step 5: Split 'down' (1-4) into 4 separate 0/1 columns
clean = clean.with_columns(
    (pl.col("down") == 1).cast(pl.Float32).alias("down_1"),
    (pl.col("down") == 2).cast(pl.Float32).alias("down_2"),
    (pl.col("down") == 3).cast(pl.Float32).alias("down_3"),
    (pl.col("down") == 4).cast(pl.Float32).alias("down_4"),
)

# Step 6: Drop unused filter columns, make everything Float32, and execute
clean = clean.drop(dropCols)
clean = clean.select(pl.all().cast(pl.Float32))
clean = clean.collect()

# Step 7: Split into matched input and target files (row i in both = same play)
inputs = clean.drop(targetCols)
targets = clean.select("success")

print("Inputs:", inputs.shape, "| Targets:", targets.shape)
inputs.write_csv("pbpCleanInput.csv")
targets.write_csv("pbpCleanTarget.csv")
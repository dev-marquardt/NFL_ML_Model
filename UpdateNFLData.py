import nflreadpy as nfl

# "seasons=True" -> All seasons
# "[2022, 2023]" -> Season ranges
# "pbp = nfl.load_pbp()" -> only current season
pbp = nfl.load_pbp(seasons=True)

# Pulls play-by-play data and save it to file
pbp.write_csv("pbp.csv")

# used to get the columns and put them in a file
#with open("blah.txt","w") as f:
#    for col, dtype in pbp.schema.items():
#        f.write(f"{col}: {dtype}\n")


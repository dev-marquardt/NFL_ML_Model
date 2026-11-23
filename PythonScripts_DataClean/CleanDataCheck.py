import polars as pl

df = pl.read_csv("pbpClean.csv", null_values=["NA", ""], infer_schema_length=10000)

print(f"Total rows: {df.height:,} | Total cols: {df.width}\n")

# Summary table: column name, dtype, null count, null %, min, max
summary = pl.DataFrame({
    "column": df.columns,
    "dtype": [str(t) for t in df.dtypes],
    "nulls": [df[c].null_count() for c in df.columns],
    "null_pct": [round(df[c].null_count() / df.height * 100, 2) for c in df.columns],
    "min": [str(df[c].min()) for c in df.columns],
    "max": [str(df[c].max()) for c in df.columns],
})

with pl.Config(tbl_rows=50, tbl_cols=10, tbl_width_chars=140):
    print(summary)

# Check if any seasons got wiped out by overly strict filters
print("\nRows per season:")
with pl.Config(tbl_rows=35):
    print(df.group_by("season").len().sort("season"))
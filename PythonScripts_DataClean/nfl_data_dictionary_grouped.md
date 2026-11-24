================================================================================
NFL PLAY-BY-PLAY DATASET: CATEGORIZED DICTIONARY REFERENCE (NFLVERSE / NFLREADPY)
================================================================================

1. GAME & SEASON IDENTIFIERS
--------------------------------------------------------------------------------
game_id
  - Desc: Unique string identifier for an NFL game formatted as {season}_{week}_{away}_{home}.
  - Data Type: String
  - Range / Values: e.g., "2023_01_KC_DET"
  - Null Behavior: No nulls.

old_game_id
  - Desc: Legacy 10-digit NFL GSIS game identifier string used for cross-referencing historical data.
  - Data Type: String
  - Range / Values: 10-digit string (e.g., "2023090700")
  - Null Behavior: No nulls for modern era.

nfl_api_id
  - Desc: Modern NFL Next Gen Stats API unique identifier UUID for the game or play.
  - Data Type: String
  - Range / Values: UUID string
  - Null Behavior: Null pre-2019.

season
  - Desc: Four-digit year representing the NFL season.
  - Data Type: Int32 / Int64
  - Range / Values: 1999 to 2026+
  - Null Behavior: No nulls.

season_type
  - Desc: Categorical indicator for the phase of the season (regular season or postseason).
  - Data Type: String
  - Range / Values: "REG", "POST"
  - Null Behavior: No nulls.

week
  - Desc: Numeric week number within the NFL season schedule.
  - Data Type: Int32 / Int64
  - Range / Values: 1 to 22 (1-18 regular season, 19-22 playoffs)
  - Null Behavior: No nulls.

game_date
  - Desc: Calendar date on which the game was played.
  - Data Type: String
  - Range / Values: "YYYY-MM-DD"
  - Null Behavior: No nulls.

start_time
  - Desc: Scheduled local kickoff time for the game.
  - Data Type: String
  - Range / Values: Kickoff timestamp string
  - Null Behavior: No nulls on valid game rows.


2. TEAM & POSSESSION CONTEXT
--------------------------------------------------------------------------------
home_team
  - Desc: Standard abbreviation of the designated home team.
  - Data Type: String
  - Range / Values: Team abbreviation (e.g., "KC", "SF", "BAL")
  - Null Behavior: No nulls.

away_team
  - Data Type: String
  - Range / Values: Standard abbreviation of the designated visiting team.
  - Data Type: String
  - Range / Values: Team abbreviation (e.g., "DET", "PHI", "BUF")
  - Null Behavior: No nulls.

posteam
  - Desc: Team currently possessing the ball on the play.
  - Data Type: String
  - Range / Values: Team abbreviation (e.g., "KC")
  - Null Behavior: Null on timeouts, end-of-quarter/game rows.

posteam_type
  - Desc: Categorical flag indicating whether the possessing team is the home or away team.
  - Data Type: String
  - Range / Values: "home", "away", null
  - Null Behavior: Null when posteam is null.

defteam
  - Desc: Team currently on defense during the play.
  - Data Type: String
  - Range / Values: Team abbreviation (e.g., "SF")
  - Null Behavior: Null on administrative plays.

location
  - Desc: Flag indicating if the game is at a team's home stadium or a neutral site.
  - Data Type: String
  - Range / Values: "Home", "Neutral"
  - Null Behavior: No nulls.

home_coach
  - Desc: Full name of the head coach of the home team.
  - Data Type: String
  - Range / Values: Coach name string
  - Null Behavior: No nulls on valid game rows.

away_coach
  - Desc: Full name of the head coach of the visiting team.
  - Data Type: String
  - Range / Values: Coach name string
  - Null Behavior: No nulls on valid game rows.

home_rest
  - Desc: Number of calendar days of rest the home team had prior to the game.
  - Data Type: Float64
  - Range / Values: Days of rest (e.g., 6, 7, 10, 14)
  - Null Behavior: No nulls on valid game rows.

away_rest
  - Desc: Number of calendar days of rest the visiting team had prior to the game.
  - Data Type: Float64
  - Range / Values: Days of rest (e.g., 6, 7, 10, 14)
  - Null Behavior: No nulls on valid game rows.

abbrev_trim
  - Desc: Cleaned and standardized team abbreviation code.
  - Data Type: String
  - Range / Values: Team code string
  - Null Behavior: No nulls.


3. PLAY IDENTIFICATION & SEQUENCING
--------------------------------------------------------------------------------
play_id
  - Desc: Unique numeric identifier assigned to a play within a specific game.
  - Data Type: Float64 / Int64
  - Range / Values: 1 to ~6000 per game
  - Null Behavior: No nulls on valid play rows.

pbp_idx
  - Desc: Internal row index number for tracking play-by-play row ordering.
  - Data Type: Float64
  - Range / Values: Sequential integer index
  - Null Behavior: No nulls.

order_sequence
  - Desc: Sequential integer representing the chronological order of play execution.
  - Data Type: Float64
  - Range / Values: Sequential integer
  - Null Behavior: Occasional nulls in legacy games.


4. GAME CLOCK & TIME METRICS
--------------------------------------------------------------------------------
qtr
  - Desc: Numerical quarter of the game (5 represents Overtime).
  - Data Type: Float64
  - Range / Values: 1.0 to 5.0
  - Null Behavior: No nulls on valid plays.

time
  - Desc: Time remaining on the game clock in the current quarter.
  - Data Type: String
  - Range / Values: "15:00" to "00:00"
  - Null Behavior: Null on non-play rows.

quarter_seconds_remaining
  - Desc: Total seconds remaining in the current quarter.
  - Data Type: Float64
  - Range / Values: 0.0 to 900.0
  - Null Behavior: Null on non-plays.

half_seconds_remaining
  - Desc: Total seconds remaining in the current half.
  - Data Type: Float64
  - Range / Values: 0.0 to 1800.0
  - Null Behavior: Null on non-plays.

game_seconds_remaining
  - Desc: Total seconds remaining in regulation play.
  - Data Type: Float64
  - Range / Values: 0.0 to 3600.0
  - Null Behavior: Null on non-plays.

game_half
  - Desc: Categorical indicator of the game half phase.
  - Data Type: String
  - Range / Values: "Half1", "Half2", "Overtime"
  - Null Behavior: No nulls on valid plays.

quarter_end
  - Desc: Binary flag indicating whether the row marks the end of a quarter.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0
  - Null Behavior: 0.0 on standard rows.

play_clock
  - Desc: Seconds remaining on the play clock when the ball was snapped.
  - Data Type: String
  - Range / Values: "0" to "40", null
  - Null Behavior: High null rate pre-2018.

end_clock_time
  - Desc: Timestamp reading on the game clock when the play concluded.
  - Data Type: String
  - Range / Values: "15:00" to "00:00", null
  - Null Behavior: Null on non-plays.

time_of_day
  - Desc: Actual wall-clock timestamp when the play occurred.
  - Data Type: String
  - Range / Values: "HH:MM:SS" timestamp string
  - Null Behavior: Sparse in older feeds.


5. DOWN, FIELD POSITION & SCRIMMAGE METRICS
--------------------------------------------------------------------------------
down
  - Desc: Current down number for the scrimmage play.
  - Data Type: Float64
  - Range / Values: 1.0, 2.0, 3.0, 4.0, null
  - Null Behavior: Null on non-scrimmage plays.

ydstogo
  - Desc: Distance in yards required to achieve a new first down.
  - Data Type: Float64
  - Range / Values: 0.0 to ~50.0
  - Null Behavior: 0 on non-plays.

yardline_100
  - Desc: Distance in yards from the line of scrimmage to the opponent's end zone.
  - Data Type: Float64
  - Range / Values: 1.0 to 99.0
  - Null Behavior: Null on kickoffs/timeouts.

yrdln
  - Desc: Formatted string description of the line of scrimmage position.
  - Data Type: String
  - Range / Values: e.g., "KC 25", "50", "BAL 12"
  - Null Behavior: Null on non-scrimmage plays.

side_of_field
  - Desc: Team abbreviation indicating which side of the 50-yard line the ball is located on.
  - Data Type: String
  - Range / Values: Team abbreviation (e.g., "KC", "SF", "MID")
  - Null Behavior: Null on kickoffs, timeouts.

goal_to_go
  - Desc: Binary flag indicating if the line to gain is the opponent's goal line.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0
  - Null Behavior: Null on non-scrimmage plays.

yards_gained
  - Desc: Net yards gained by the offense on the play.
  - Data Type: Float64
  - Range / Values: ~ -40.0 to 99.0, null
  - Null Behavior: Null on non-plays / aborted rows.

end_yardline
  - Desc: Formatted string description of the field position where the play ended.
  - Data Type: String
  - Range / Values: e.g., "KC 35", "BAL 10", null
  - Null Behavior: Null on non-plays.

missing_yardline_data
  - Desc: Binary indicator flag showing if yardline positional data is absent or corrupt.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0
  - Null Behavior: 0.0 on standard rows.


6. PLAY CLASSIFICATION & DATASET CONTROL FLAGS
--------------------------------------------------------------------------------
play
  - Desc: Binary indicator flag marking a valid play row.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0
  - Null Behavior: No nulls on valid rows.

play_type
  - Desc: Standardized play category string.
  - Data Type: String
  - Range / Values: "pass", "run", "punt", "field_goal", "kickoff", "no_play", "qb_kneel", "qb_spike"
  - Null Behavior: Null on end-of-quarter rows; "no_play" on penalties.

play_type_nfl
  - Desc: Unmodified raw play classification code directly from the official NFL API feed.
  - Data Type: String
  - Range / Values: Raw play type code (e.g., "GAME_START", "PAT", "PASS")
  - Null Behavior: Null on some legacy rows.

st_play_type
  - Desc: Categorical classification specific to special teams plays.
  - Data Type: String
  - Range / Values: "Punt", "Field Goal", "Kickoff", "Extra Point", null
  - Null Behavior: Null on non-special teams plays.

type
  - Desc: Internal source feed play type code.
  - Data Type: String
  - Range / Values: Play type string code
  - Null Behavior: Varies by feed.

aborted_play
  - Desc: Binary indicator flag for botched snaps, aborted handoffs, or unexecuted plays.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0
  - Null Behavior: 0.0 on normal plays.

play_deleted
  - Desc: Binary flag indicating if a play was officially erased or nullified from official statistics.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: Null in older feeds; 1.0 if deleted.

special
  - Desc: Binary flag indicating if a play is a special teams execution.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0
  - Null Behavior: 0.0 for scrimmage plays.

special_teams_play
  - Desc: Secondary binary indicator flag for special teams plays.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: Null pre-2011.

qb_kneel
  - Desc: Binary flag indicating if the quarterback executed a kneel-down to run the clock.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0
  - Null Behavior: 0.0 for normal plays.

qb_spike
  - Desc: Binary flag indicating if the quarterback spiked the ball to stop the game clock.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0
  - Null Behavior: 0.0 for normal plays.


7. PLAY EXECUTION & TACTICAL SCHEME
--------------------------------------------------------------------------------
shotgun
  - Desc: Binary indicator flag showing if the quarterback lined up in shotgun formation.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0
  - Null Behavior: Sparse pre-2006.

no_huddle
  - Desc: Binary indicator flag showing if the offense ran a hurry-up / no-huddle play.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0
  - Null Behavior: 0.0 on standard plays.

qb_dropback
  - Desc: Binary indicator showing if the play involved a quarterback dropback (passes, sacks, scrambles).
  - Data Type: Float64
  - Range / Values: 0.0, 1.0
  - Null Behavior: Null on non-scrimmage plays.

qb_scramble
  - Desc: Binary indicator flag showing if the quarterback scrambled out of the pocket on a dropback.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0
  - Null Behavior: 0.0 on normal plays.

pass_length
  - Desc: Categorical target depth of a pass relative to 15 air yards.
  - Data Type: String
  - Range / Values: "short", "deep", null
  - Null Behavior: Null on non-pass plays.

pass_location
  - Desc: Horizontal direction of the pass trajectory relative to the field width.
  - Data Type: String
  - Range / Values: "left", "middle", "right", null
  - Null Behavior: Null on non-pass plays.

air_yards
  - Desc: Distance in yards from the line of scrimmage to the target receiver catch location.
  - Data Type: Float64
  - Range / Values: ~ -15.0 to 65.0
  - Null Behavior: Null on non-pass plays or throwaways.

yards_after_catch
  - Desc: Distance in yards gained by the receiver after catching the pass.
  - Data Type: Float64
  - Range / Values: ~ -10.0 to 99.0
  - Null Behavior: Null on incomplete passes / non-passes.

run_location
  - Desc: Horizontal direction path chosen by the rusher relative to the offensive line.
  - Data Type: String
  - Range / Values: "left", "middle", "right", null
  - Null Behavior: Null on non-rush plays.

run_gap
  - Desc: Specific offensive line gap (guard, tackle, end) penetrated by the rusher.
  - Data Type: String
  - Range / Values: "guard", "tackle", "end", null
  - Null Behavior: Null on interior rushes or non-rushes.


8. PLAY OUTCOMES & STATISTICAL EVENTS
--------------------------------------------------------------------------------
first_down
  - Desc: Binary indicator flag showing if a first down was achieved on the play.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: Null on special teams / non-scrimmage plays.

first_down_rush
  - Desc: Binary flag indicating a first down was converted via a rushing play.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: 0.0 on non-rushing plays.

first_down_pass
  - Desc: Binary flag indicating a first down was converted via a passing play.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: 0.0 on non-passing plays.

first_down_penalty
  - Desc: Binary flag indicating a first down was awarded due to a defensive penalty.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: 0.0 on non-penalty plays.

third_down_converted
  - Desc: Binary flag indicating successful first down conversion on 3rd down.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: Null when down != 3.

third_down_failed
  - Desc: Binary flag indicating failure to convert a first down on 3rd down.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: Null when down != 3.

fourth_down_converted
  - Desc: Binary flag indicating successful first down conversion on 4th down.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: Null when down != 4.

fourth_down_failed
  - Desc: Binary flag indicating failure to convert a first down on 4th down.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: Null when down != 4.

incomplete_pass
  - Desc: Binary flag indicating an uncompleted pass attempt.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: Null on non-pass attempts.

touchdown
  - Desc: Binary flag indicating a touchdown was scored on the play.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: 0.0 on non-scoring plays.

pass_touchdown
  - Desc: Binary flag indicating a touchdown scored via a passing play.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: 0.0 on non-pass plays.

rush_touchdown
  - Desc: Binary flag indicating a touchdown scored via a rushing play.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: 0.0 on non-rush plays.

return_touchdown
  - Desc: Binary flag indicating a touchdown scored via punt, kickoff, or turnover return.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: 0.0 on standard plays.

interception
  - Desc: Binary flag indicating a pass was intercepted by the defense.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: Null on non-pass attempts.

fumble
  - Desc: Binary flag indicating a ball was fumbled during the play.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: 0.0 on normal plays.

fumble_forced
  - Desc: Binary flag indicating a fumble was caused by defender contact.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: Null when fumble == 0.

fumble_not_forced
  - Desc: Binary flag indicating an unforced fumble (e.g., dropped snap or muffed handoff).
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: Null when fumble == 0.

fumble_out_of_bounds
  - Desc: Binary flag indicating a fumbled ball rolled out of bounds.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: Null when fumble == 0.

fumble_lost
  - Desc: Binary flag indicating a fumble was recovered by the opposing team.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: Null when fumble == 0.

sack
  - Desc: Binary flag indicating the passer was tackled behind the line of scrimmage.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: Null on non-pass dropbacks.

safety
  - Desc: Binary flag indicating a 2-point safety occurred on the play.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: 0.0 on normal plays.

penalty
  - Data Type: Float64
  - Desc: Binary flag indicating an official penalty was called on the play.
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: 0.0 on non-penalty plays.

tackled_for_loss
  - Desc: Binary flag indicating a offensive ball carrier was tackled behind the line of scrimmage.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: Null on non-scrimmage plays.

touchback
  - Desc: Binary flag indicating a kick or punt resulted in a touchback.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0
  - Null Behavior: 0.0 on non-kicking plays.

punt_blocked
  - Desc: Binary flag indicating a punt attempt was blocked by the defense.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: Null on non-punt plays.

success
  - Desc: Binary indicator flag marking whether a play generated positive Expected Points Added (EPA > 0).
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: Null on non-plays.


9. SCORE, TIMEOUT & GAME DIFFERENTIALS
--------------------------------------------------------------------------------
posteam_score
  - Desc: Current score of the possessing team prior to the snap.
  - Data Type: Float64
  - Range / Values: 0.0 to ~60.0
  - Null Behavior: Null on non-possession rows.

defteam_score
  - Desc: Current score of the defending team prior to the snap.
  - Data Type: Float64
  - Range / Values: 0.0 to ~60.0
  - Null Behavior: Null on non-possession rows.

score_differential
  - Desc: Point differential from the possessing team's perspective (posteam_score - defteam_score) pre-snap.
  - Data Type: Float64
  - Range / Values: ~ -60.0 to +60.0
  - Null Behavior: Null on non-plays.

posteam_score_post
  - Desc: Score of the possessing team immediately after the play concluded.
  - Data Type: Float64
  - Range / Values: 0.0 to ~60.0
  - Null Behavior: Null on non-plays.

defteam_score_post
  - Desc: Score of the defending team immediately after the play concluded.
  - Data Type: Float64
  - Range / Values: 0.0 to ~60.0
  - Null Behavior: Null on non-plays.

score_differential_post
  - Desc: Point differential from the possessing team's perspective immediately post-play.
  - Data Type: Float64
  - Range / Values: ~ -60.0 to +60.0
  - Null Behavior: Null on non-plays.

total_home_score
  - Desc: Total points scored by the home team prior to the snap.
  - Data Type: Float64
  - Range / Values: 0.0 to ~60.0
  - Null Behavior: No nulls on valid plays.

total_away_score
  - Desc: Total points scored by the visiting team prior to the snap.
  - Data Type: Float64
  - Range / Values: 0.0 to ~60.0
  - Null Behavior: No nulls on valid plays.

home_score
  - Desc: Final end-of-game total points scored by the home team.
  - Data Type: Float64
  - Range / Values: Final home points
  - Null Behavior: No nulls on completed game rows.

away_score
  - Desc: Final end-of-game total points scored by the visiting team.
  - Data Type: Float64
  - Range / Values: Final away points
  - Null Behavior: No nulls on completed game rows.

sp
  - Desc: Binary flag indicating if points were scored by either team on the play.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0
  - Null Behavior: 0.0 on non-scoring plays.

posteam_timeouts_remaining
  - Desc: Count of timeouts remaining for the possessing team in the current half.
  - Data Type: Float64
  - Range / Values: 0.0 to 3.0
  - Null Behavior: Null on non-plays.

defteam_timeouts_remaining
  - Desc: Count of timeouts remaining for the defending team in the current half.
  - Data Type: Float64
  - Range / Values: 0.0 to 3.0
  - Null Behavior: Null on non-plays.

home_timeouts_remaining
  - Desc: Count of timeouts remaining for the home team in the current half.
  - Data Type: Float64
  - Range / Values: 0.0 to 3.0
  - Null Behavior: No nulls on valid plays.

away_timeouts_remaining
  - Desc: Count of timeouts remaining for the visiting team in the current half.
  - Data Type: Float64
  - Range / Values: 0.0 to 3.0
  - Null Behavior: No nulls on valid plays.

timeout
  - Desc: Binary indicator flag showing if a timeout was taken on the play.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0
  - Null Behavior: 0.0 on standard plays.

timeout_team
  - Desc: Team abbreviation string of the team that called the timeout.
  - Data Type: String
  - Range / Values: Team abbreviation string, null
  - Null Behavior: Null when timeout == 0.

td_team
  - Desc: Team abbreviation string of the team that scored a touchdown.
  - Data Type: String
  - Range / Values: Team abbreviation string, null
  - Null Behavior: Null on non-TD plays.

td_player_name
  - Desc: Full name string of the player who scored a touchdown.
  - Data Type: String
  - Range / Values: Player name string, null
  - Null Behavior: Null on non-TD plays.

td_player_id
  - Data Type: String
  - Desc: Unique GSIS ID string of the player who scored a touchdown.
  - Range / Values: GSIS player ID string, null
  - Null Behavior: Null on non-TD plays.

next_score_type
  - Desc: Categorical type of the next scoring event that occurred in the game.
  - Data Type: String
  - Range / Values: "TD", "FG", "Safety", "No_Score", null
  - Null Behavior: Null on non-plays.


10. EXPECTED POINTS (EP & EPA) METRICS
--------------------------------------------------------------------------------
ep
  - Desc: Expected points for the possessing team prior to the snap.
  - Data Type: Float64
  - Range / Values: ~ -3.0 to +7.0
  - Null Behavior: Null on non-plays / kickoffs.

ep_post
  - Desc: Expected points calculated for the possessing team immediately after the play.
  - Data Type: Float64
  - Range / Values: ~ -3.0 to +7.0
  - Null Behavior: Null on non-plays.

epa
  - Desc: Net Expected Points Added by the play outcome (ep_post - ep).
  - Data Type: Float64
  - Range / Values: ~ -10.0 to +10.0
  - Null Behavior: Null on non-scrimmage plays.

total_home_epa
  - Desc: Cumulative running EPA accrued by the home team during the game.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Resets per game.

total_away_epa
  - Desc: Cumulative running EPA accrued by the visiting team during the game.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Resets per game.

total_home_rush_epa
  - Desc: Cumulative running EPA accrued by the home team on rushing plays.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Null on non-rushing plays.

total_away_rush_epa
  - Desc: Cumulative running EPA accrued by the visiting team on rushing plays.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Null on non-rushing plays.

total_home_pass_epa
  - Desc: Cumulative running EPA accrued by the home team on passing plays.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Null on non-pass plays.

total_away_pass_epa
  - Desc: Cumulative running EPA accrued by the visiting team on passing plays.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Null on non-pass plays.

total_home_comp_air_epa
  - Desc: Cumulative running air EPA accumulated by the home team on completed passes.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Updated on completions.

total_away_comp_air_epa
  - Desc: Cumulative running air EPA accumulated by the visiting team on completed passes.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Updated on completions.

total_home_comp_yac_epa
  - Desc: Cumulative running YAC EPA accumulated by the home team on completed passes.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Updated on completions.

total_away_comp_yac_epa
  - Desc: Cumulative running YAC EPA accumulated by the visiting team on completed passes.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Updated on completions.

total_home_raw_air_epa
  - Desc: Cumulative raw air EPA generated by the home team on all pass attempts.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Updated on pass plays.

total_away_raw_air_epa
  - Desc: Cumulative raw air EPA generated by the visiting team on all pass attempts.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Updated on pass plays.

total_home_raw_yac_epa
  - Desc: Cumulative raw YAC EPA generated by the home team on all pass attempts.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Updated on pass plays.

total_away_raw_yac_epa
  - Desc: Cumulative raw YAC EPA generated by the visiting team on all pass attempts.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Updated on pass plays.

air_epa
  - Desc: EPA attributed strictly to the throw length (air distance) past the line of scrimmage.
  - Data Type: Float64
  - Range / Values: ~ -5.0 to +7.0
  - Null Behavior: Null on non-pass plays.

yac_epa
  - Desc: EPA attributed to yards gained by the receiver after making the catch.
  - Data Type: Float64
  - Range / Values: ~ -5.0 to +7.0
  - Null Behavior: Null on incomplete passes / non-pass plays.

comp_air_epa
  - Desc: Air EPA generated specifically on completed pass plays.
  - Data Type: Float64
  - Range / Values: ~ -5.0 to +7.0
  - Null Behavior: Null on incomplete passes.

comp_yac_epa
  - Desc: YAC EPA generated specifically on completed pass plays.
  - Data Type: Float64
  - Range / Values: ~ -5.0 to +7.0
  - Null Behavior: Null on incomplete passes.

raw_air_epa
  - Desc: Unadjusted air EPA calculation prior to completion/incompletion conditioning.
  - Data Type: Float64
  - Range / Values: ~ -5.0 to +7.0
  - Null Behavior: Null on non-pass plays.

raw_yac_epa
  - Desc: Unadjusted YAC EPA calculation prior to completion/incompletion conditioning.
  - Data Type: Float64
  - Range / Values: ~ -5.0 to +7.0
  - Null Behavior: Null on non-pass plays.

qb_epa
  - Desc: Custom nflfastR EPA metric assigned to the quarterback (includes passes, sacks, scrambles, penalties).
  - Data Type: Float64
  - Range / Values: ~ -10.0 to +10.0
  - Null Behavior: Null on non-QB plays.

ep_next_score
  - Desc: Expected points value of the next score to occur in the game.
  - Data Type: Float64
  - Range / Values: ~ -7.0 to +7.0
  - Null Behavior: Null on non-plays.

ep_diff
  - Desc: Difference between the current play Expected Points and the next score EP.
  - Data Type: Float64
  - Range / Values: ~ -14.0 to +14.0
  - Null Behavior: Null on non-plays.


11. WIN PROBABILITY (WP & WPA) METRICS
--------------------------------------------------------------------------------
wp
  - Desc: Estimated win probability for the possessing team prior to the snap.
  - Data Type: Float64
  - Range / Values: 0.0 to 1.0
  - Null Behavior: Null on non-plays.

def_wp
  - Desc: Estimated win probability for the defending team prior to the snap (1 - wp).
  - Data Type: Float64
  - Range / Values: 0.0 to 1.0
  - Null Behavior: Null on non-plays.

home_wp
  - Desc: Estimated win probability for the home team prior to the snap.
  - Data Type: Float64
  - Range / Values: 0.0 to 1.0
  - Null Behavior: Null on non-plays.

away_wp
  - Desc: Estimated win probability for the visiting team prior to the snap.
  - Data Type: Float64
  - Range / Values: 0.0 to 1.0
  - Null Behavior: Null on non-plays.

wpa
  - Desc: Win Probability Added by the possessing team as a result of the play.
  - Data Type: Float64
  - Range / Values: ~ -1.0 to +1.0
  - Null Behavior: Null on non-plays.

vegas_wp
  - Desc: Possessing team pre-snap win probability incorporating pre-game betting spreads.
  - Data Type: Float64
  - Range / Values: 0.0 to 1.0
  - Null Behavior: Null on non-plays.

vegas_home_wp
  - Desc: Home team pre-snap win probability incorporating pre-game betting spreads.
  - Data Type: Float64
  - Range / Values: 0.0 to 1.0
  - Null Behavior: Null on non-plays.

vegas_wpa
  - Desc: Win Probability Added calculated using the Vegas-adjusted model.
  - Data Type: Float64
  - Range / Values: ~ -1.0 to +1.0
  - Null Behavior: Null on non-plays.

vegas_home_wpa
  - Desc: Vegas-adjusted Win Probability Added accumulated by the home team on the play.
  - Data Type: Float64
  - Range / Values: ~ -1.0 to +1.0
  - Null Behavior: Null on non-plays.

wp_post
  - Desc: Win probability for the possessing team immediately after the play.
  - Data Type: Float64
  - Range / Values: 0.0 to 1.0
  - Null Behavior: Null on non-plays.

def_wp_post
  - Desc: Win probability for the defending team immediately after the play.
  - Data Type: Float64
  - Range / Values: 0.0 to 1.0
  - Null Behavior: Null on non-plays.

home_wp_post
  - Desc: Win probability for the home team immediately after the play.
  - Data Type: Float64
  - Range / Values: 0.0 to 1.0
  - Null Behavior: Null on non-plays.

away_wp_post
  - Desc: Win probability for the visiting team immediately after the play.
  - Data Type: Float64
  - Range / Values: 0.0 to 1.0
  - Null Behavior: Null on non-plays.

home_wp_post_2
  - Desc: Secondary win probability model post-play estimate for the home team.
  - Data Type: Float64
  - Range / Values: 0.0 to 1.0
  - Null Behavior: Secondary model calculation.

away_wp_post_2
  - Desc: Secondary win probability model post-play estimate for the visiting team.
  - Data Type: Float64
  - Range / Values: 0.0 to 1.0
  - Null Behavior: Secondary model calculation.

total_home_rush_wpa
  - Desc: Cumulative running WPA accumulated by the home team on rushing plays.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Updated on rush plays.

total_away_rush_wpa
  - Desc: Cumulative running WPA accumulated by the visiting team on rushing plays.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Updated on rush plays.

total_home_pass_wpa
  - Desc: Cumulative running WPA accumulated by the home team on passing plays.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Updated on pass plays.

total_away_pass_wpa
  - Desc: Cumulative running WPA accumulated by the visiting team on passing plays.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Updated on pass plays.

total_home_comp_air_wpa
  - Desc: Cumulative running completed air WPA accumulated by the home team.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Updated on completions.

total_away_comp_air_wpa
  - Desc: Cumulative running completed air WPA accumulated by the visiting team.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Updated on completions.

total_home_comp_yac_wpa
  - Desc: Cumulative running completed YAC WPA accumulated by the home team.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Updated on completions.

total_away_comp_yac_wpa
  - Desc: Cumulative running completed YAC WPA accumulated by the visiting team.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Updated on completions.

total_home_raw_air_wpa
  - Desc: Cumulative raw air WPA generated by the home team across all pass attempts.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Updated on pass attempts.

total_away_raw_air_wpa
  - Desc: Cumulative raw air WPA generated by the visiting team across all pass attempts.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Updated on pass attempts.

total_home_raw_yac_wpa
  - Desc: Cumulative raw YAC WPA generated by the home team across all pass attempts.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Updated on pass attempts.

total_away_raw_yac_wpa
  - Desc: Cumulative raw YAC WPA generated by the visiting team across all pass attempts.
  - Data Type: Float64
  - Range / Values: Cumulative float
  - Null Behavior: Updated on pass attempts.

air_wpa
  - Desc: Win probability added attributed to the air distance of the pass.
  - Data Type: Float64
  - Range / Values: ~ -1.0 to +1.0
  - Null Behavior: Null on non-pass plays.

yac_wpa
  - Desc: Win probability added attributed to receiver yards gained after catch.
  - Data Type: Float64
  - Range / Values: ~ -1.0 to +1.0
  - Null Behavior: Null on incomplete passes.

comp_air_wpa
  - Desc: Air WPA generated on completed pass plays.
  - Data Type: Float64
  - Range / Values: ~ -1.0 to +1.0
  - Null Behavior: Null on incomplete passes.

comp_yac_wpa
  - Desc: YAC WPA generated on completed pass plays.
  - Data Type: Float64
  - Range / Values: ~ -1.0 to +1.0
  - Null Behavior: Null on incomplete passes.

raw_air_wpa
  - Desc: Unadjusted air WPA calculation prior to pass outcome.
  - Data Type: Float64
  - Range / Values: ~ -1.0 to +1.0
  - Null Behavior: Null on non-pass plays.

raw_yac_wpa
  - Desc: Unadjusted YAC WPA calculation prior to pass outcome.
  - Data Type: Float64
  - Range / Values: ~ -1.0 to +1.0
  - Null Behavior: Null on non-pass plays.

qb_wpa
  - Desc: Custom nflfastR WPA metric assigned directly to the quarterback.
  - Data Type: Float64
  - Range / Values: ~ -1.0 to +1.0
  - Null Behavior: Null on non-QB plays.


12. ADVANCED EXPECTED METRICS & PROJECTIONS
--------------------------------------------------------------------------------
xpass
  - Desc: Model-estimated probability that the offense will execute a pass play prior to snap.
  - Data Type: Float64
  - Range / Values: 0.0 to 1.0
  - Null Behavior: Null on non-scrimmage plays / penalties.

pass_oe
  - Desc: Pass Over Expected percentage (actual play choice vs xpass model prediction).
  - Data Type: Float64
  - Range / Values: ~ -100.0 to +100.0
  - Null Behavior: Null when xpass is null.

cp
  - Desc: Model-estimated completion probability based on throw distance, location, and defensive tracking.
  - Data Type: Float64
  - Range / Values: 0.0 to 1.0
  - Null Behavior: Null on non-pass attempts or throwaways.

cpoe
  - Desc: Completion Percentage Over Expected ((actual completion - cp) * 100).
  - Data Type: Float64
  - Range / Values: ~ -100.0 to +100.0
  - Null Behavior: Null on non-pass attempts or throwaways.

xyac_epa
  - Desc: Expected YAC EPA predicted by the catch-location spatial model.
  - Data Type: Float64
  - Range / Values: ~ -5.0 to +7.0
  - Null Behavior: Null on non-pass attempts.

xyac_mean_yardage
  - Desc: Expected mean YAC yardage predicted by the catch-location model.
  - Data Type: Float64
  - Range / Values: 0.0 to ~80.0
  - Null Behavior: Null on non-pass attempts.

xyac_median_yardage
  - Desc: Expected median YAC yardage predicted by the catch-location model.
  - Data Type: Float64
  - Range / Values: 0.0 to ~80.0
  - Null Behavior: Null on non-pass attempts.

xyac_fd
  - Desc: Model-estimated probability of gaining a first down via YAC.
  - Data Type: Float64
  - Range / Values: 0.0 to 1.0
  - Null Behavior: Null on non-pass attempts.

xyac_success
  - Desc: Model-estimated probability of generating positive EPA via YAC post-catch.
  - Data Type: Float64
  - Range / Values: 0.0 to 1.0
  - Null Behavior: Null on non-pass attempts.


13. OFFENSIVE PLAYER ATTRIBUTION
--------------------------------------------------------------------------------
passer_player_id
  - Desc: Unique GSIS identifier for the primary passer on the play.
  - Data Type: String
  - Range / Values: GSIS player ID string (e.g., "00-0033873")
  - Null Behavior: Null on non-pass plays.

passer_player_name
  - Desc: Abbreviated primary name of the passer.
  - Data Type: String
  - Range / Values: e.g., "P.Mahomes"
  - Null Behavior: Null on non-pass plays.

passer_id
  - Desc: Legacy passer GSIS identifier field.
  - Data Type: String
  - Range / Values: GSIS player ID string
  - Null Behavior: Null on non-pass plays.

passer_name
  - Desc: Legacy passer name field.
  - Data Type: String
  - Range / Values: Player name string
  - Null Behavior: Null on non-pass plays.

passing_yards
  - Desc: Official box-score passing yards credited to the passer.
  - Data Type: Float64
  - Range / Values: ~ -15.0 to 99.0
  - Null Behavior: Null on incomplete passes / non-passes.

receiver_player_id
  - Desc: Unique GSIS identifier for the targeted receiver.
  - Data Type: String
  - Range / Values: GSIS player ID string
  - Null Behavior: Null on non-targeted pass plays.

receiver_player_name
  - Desc: Abbreviated primary name of the targeted receiver.
  - Data Type: String
  - Range / Values: e.g., "J.Jefferson"
  - Null Behavior: Null on non-targeted pass plays.

receiver_id
  - Desc: Legacy receiver GSIS identifier field.
  - Data Type: String
  - Range / Values: GSIS player ID string
  - Null Behavior: Null on non-targeted pass plays.

receiver_name
  - Desc: Legacy receiver name field.
  - Data Type: String
  - Range / Values: Player name string
  - Null Behavior: Null on non-targeted pass plays.

receiving_yards
  - Desc: Official box-score receiving yards credited to the receiver.
  - Data Type: Float64
  - Range / Values: ~ -15.0 to 99.0
  - Null Behavior: Null on incomplete passes / non-passes.

rusher_player_id
  - Desc: Unique GSIS identifier for the designated ball carrier.
  - Data Type: String
  - Range / Values: GSIS player ID string
  - Null Behavior: Null on non-rush plays.

rusher_player_name
  - Desc: Abbreviated primary name of the rusher.
  - Data Type: String
  - Range / Values: e.g., "D.Henry"
  - Null Behavior: Null on non-rush plays.

rusher_id
  - Desc: Legacy rusher GSIS identifier field.
  - Data Type: String
  - Range / Values: GSIS player ID string
  - Null Behavior: Null on non-rush plays.

rusher_name
  - Desc: Legacy rusher name field.
  - Data Type: String
  - Range / Values: Player name string
  - Null Behavior: Null on non-rush plays.

rushing_yards
  - Desc: Official box-score rushing yards credited to the rusher.
  - Data Type: Float64
  - Range / Values: ~ -20.0 to 99.0
  - Null Behavior: Null on non-rush plays.

lateral_receiver_player_id
  - Desc: GSIS identifier of the player receiving a lateral on a pass play.
  - Data Type: String
  - Range / Values: GSIS player ID string, null
  - Null Behavior: Null if no lateral receiver.

lateral_receiver_player_name
  - Desc: Name of the player receiving a lateral on a pass play.
  - Data Type: String
  - Range / Values: Player name string, null
  - Null Behavior: Null if no lateral receiver.

lateral_receiving_yards
  - Desc: Receiving yards accrued by a lateral receiver after taking the pitch.
  - Data Type: Float64
  - Range / Values: Float yards, null
  - Null Behavior: Null if no lateral receiver.

lateral_rusher_player_id
  - Desc: GSIS identifier of the player receiving a lateral on a run play.
  - Data Type: String
  - Range / Values: GSIS player ID string, null
  - Null Behavior: Null if no lateral rusher.

lateral_rusher_player_name
  - Desc: Name of the player receiving a lateral on a run play.
  - Data Type: String
  - Range / Values: Player name string, null
  - Null Behavior: Null if no lateral rusher.

lateral_rushing_yards
  - Desc: Rushing yards accrued by a lateral rusher after taking the pitch.
  - Data Type: Float64
  - Range / Values: Float yards, null
  - Null Behavior: Null if no lateral rusher.

lateral_reception_player_id
  - Desc: GSIS identifier of the player catching a lateral pass.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null if no lateral reception.

lateral_reception_player_name
  - Desc: Name of the player catching a lateral pass.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null if no lateral reception.

lateral_rush_player_id
  - Desc: GSIS identifier of the player executing a lateral rush.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null if no lateral rush.

lateral_rush_player_name
  - Desc: Name of the player executing a lateral rush.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null if no lateral rush.

lateral_return_player_id
  - Desc: GSIS identifier of the player carrying a lateral return on special teams.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null if no lateral return.

lateral_return_player_name
  - Desc: Name of the player carrying a lateral return on special teams.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null if no lateral return.

lateral_recovery_player_id
  - Desc: GSIS identifier of the player recovering a lateral fumble.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null if no lateral recovery.

lateral_recovery_player_name
  - Desc: Name of the player recovering a lateral fumble.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null if no lateral recovery.


14. DEFENSIVE PLAYER ATTRIBUTION
--------------------------------------------------------------------------------
interception_player_id
  - Desc: GSIS identifier of the defender who intercepted the pass.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null on non-interceptions.

interception_player_name
  - Desc: Name of the defender who intercepted the pass.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null on non-interceptions.

intercepter_player_id
  - Desc: Alternate field for the intercepting defender's GSIS ID.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null on non-interceptions.

intercepter_player_name
  - Desc: Alternate field for the intercepting defender's name.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null on non-interceptions.

interception_yards
  - Desc: Return yardage gained by the defender following an interception.
  - Data Type: Float64
  - Range / Values: Return yards float, null
  - Null Behavior: Null on non-interceptions.

sack_player_id
  - Desc: Primary defender GSIS identifier credited with a sack.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null when sack == 0.

sack_player_name
  - Desc: Name of the primary defender credited with a sack.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null when sack == 0.

sack_player_1_id
  - Desc: Secondary identifier field for the primary sacker.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null when sack == 0.

sack_player_id_2
  - Desc: GSIS identifier of the second defender credited with a shared sack.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null unless multiple sackers.

sack_player_name_2
  - Desc: Name of the second defender credited with a shared sack.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null unless multiple sackers.

sack_player_2_id
  - Desc: Legacy field for the second sacker GSIS ID.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null unless multiple sackers.

half_sack_1_player_id
  - Desc: GSIS ID of the first defender sharing a half-sack split.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null unless half-sack recorded.

half_sack_1_player_name
  - Desc: Name of the first defender sharing a half-sack split.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null unless half-sack recorded.

half_sack_1_id
  - Desc: Legacy ID field for the first half-sack defender.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null unless half-sack recorded.

half_sack_2_player_id
  - Desc: GSIS ID of the second defender sharing a half-sack split.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null unless half-sack recorded.

half_sack_2_player_name
  - Desc: Name of the second defender sharing a half-sack split.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null unless half-sack recorded.

half_sack_2_id
  - Desc: Legacy ID field for the second half-sack defender.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null unless half-sack recorded.

forced_fumble_player_1_team
  - Desc: Team abbreviation of the primary defender who forced a fumble.
  - Data Type: String
  - Range / Values: Team abbreviation, null
  - Null Behavior: Null when forced fumble == 0.

forced_fumble_player_1_player_id
  - Desc: GSIS identifier of the primary defender who forced a fumble.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null when forced fumble == 0.

forced_fumble_player_1_player_name
  - Desc: Name of the primary defender who forced a fumble.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null when forced fumble == 0.

forced_fumble_player_1_id
  - Desc: Legacy ID field for the primary forced fumble defender.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null when forced fumble == 0.

forced_fumble_player_2_team
  - Desc: Team abbreviation of the secondary defender involved in forcing a fumble.
  - Data Type: String
  - Range / Values: Team abbreviation, null
  - Null Behavior: Null unless 2 defenders forced fumble.

forced_fumble_player_2_player_id
  - Desc: GSIS identifier of the secondary defender involved in forcing a fumble.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null unless 2 defenders forced fumble.

forced_fumble_player_2_player_name
  - Desc: Name of the secondary defender involved in forcing a fumble.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null unless 2 defenders forced fumble.

forced_fumble_player_2_id
  - Desc: Legacy ID field for the secondary forced fumble defender.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null unless 2 defenders forced fumble.

solo_tackle
  - Desc: Binary flag indicating an unassisted solo tackle by a single defender.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: Null on non-tackle plays.

solo_tackle_1_team
  - Desc: Team abbreviation of the defender credited with solo tackle #1.
  - Data Type: String
  - Range / Values: Team abbreviation, null
  - Null Behavior: Null when solo_tackle == 0.

solo_tackle_1_player_id
  - Desc: GSIS identifier of the defender credited with solo tackle #1.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null when solo_tackle == 0.

solo_tackle_1_player_name
  - Desc: Name of the defender credited with solo tackle #1.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null when solo_tackle == 0.

solo_tackle_1_id
  - Desc: Legacy ID field for solo tackler #1.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null when solo_tackle == 0.

solo_tackle_2_team
  - Desc: Team abbreviation of a secondary defender credited with an unassisted solo tackle.
  - Data Type: String
  - Range / Values: Team abbreviation, null
  - Null Behavior: Sparse / null.

solo_tackle_2_player_id
  - Desc: GSIS identifier of secondary solo tackler #2.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Sparse / null.

solo_tackle_2_player_name
  - Desc: Name of secondary solo tackler #2.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Sparse / null.

solo_tackle_2_id
  - Desc: Legacy ID field for solo tackler #2.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Sparse / null.

assist_tackle_1_player_id
  - Desc: GSIS identifier of defender #1 credited with an assisted tackle.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null if no assisted tackle.

assist_tackle_1_player_name
  - Desc: Name of defender #1 credited with an assisted tackle.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null if no assisted tackle.

assist_tackle_1_team
  - Desc: Team abbreviation of assist tackler #1.
  - Data Type: String
  - Range / Values: Team abbreviation, null
  - Null Behavior: Null if no assisted tackle.

assist_tackle_1_id
  - Desc: Legacy ID field for assist tackler #1.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null if no assisted tackle.

assist_tackle_2_player_id
  - Desc: GSIS identifier of defender #2 credited with an assisted tackle.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null unless 2+ assist tacklers.

assist_tackle_2_player_name
  - Desc: Name of defender #2 credited with an assisted tackle.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null unless 2+ assist tacklers.

assist_tackle_2_team
  - Desc: Team abbreviation of assist tackler #2.
  - Data Type: String
  - Range / Values: Team abbreviation, null
  - Null Behavior: Null unless 2+ assist tacklers.

assist_tackle_2_id
  - Desc: Legacy ID field for assist tackler #2.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null unless 2+ assist tacklers.

assist_tackle_3_player_id
  - Desc: GSIS identifier of defender #3 credited with an assisted tackle.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null unless 3+ assist tacklers.

assist_tackle_3_player_name
  - Desc: Name of defender #3 credited with an assisted tackle.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null unless 3+ assist tacklers.

assist_tackle_3_team
  - Desc: Team abbreviation of assist tackler #3.
  - Data Type: String
  - Range / Values: Team abbreviation, null
  - Null Behavior: Null unless 3+ assist tacklers.

assist_tackle_3_id
  - Desc: Legacy ID field for assist tackler #3.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null unless 3+ assist tacklers.

assist_tackle_4_player_id
  - Desc: GSIS identifier of defender #4 credited with an assisted tackle.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null unless 4 assist tacklers.

assist_tackle_4_player_name
  - Desc: Name of defender #4 credited with an assisted tackle.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null unless 4 assist tacklers.

assist_tackle_4_team
  - Desc: Team abbreviation of assist tackler #4.
  - Data Type: String
  - Range / Values: Team abbreviation, null
  - Null Behavior: Null unless 4 assist tacklers.

assist_tackle_4_id
  - Desc: Legacy ID field for assist tackler #4.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null unless 4 assist tacklers.

tackle_with_assist
  - Desc: Binary flag indicating if the tackle involved multiple defenders assisting.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: Null on non-tackle plays.

pass_defense_1_player_id
  - Desc: GSIS identifier of primary defender credited with a pass deflection/breakup.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null if no pass defense.

pass_defense_1_player_name
  - Desc: Name of primary defender credited with a pass deflection/breakup.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null if no pass defense.

pass_defense_1_id
  - Desc: Legacy ID field for primary pass defender.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null if no pass defense.

pass_defense_2_player_id
  - Desc: GSIS identifier of secondary defender credited with a pass deflection.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null unless 2 defenders defensed pass.

pass_defense_2_player_name
  - Desc: Name of secondary defender credited with a pass deflection.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null unless 2 defenders defensed pass.

pass_defense_2_id
  - Desc: Legacy ID field for secondary pass defender.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null unless 2 defenders defensed pass.

defender_player_id
  - Desc: Primary defender GSIS identifier attributed to the main defensive play event.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null on non-defensive attribution.

defender_player_name
  - Desc: Name of the primary defender attributed to the play event.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null on non-defensive attribution.

defender_id
  - Desc: Legacy primary defender GSIS ID.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null on non-defensive attribution.

defender_name
  - Desc: Legacy primary defender name.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null on non-defensive attribution.

safety_player_id
  - Desc: GSIS identifier of defender credited with forcing a safety.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null on non-safety plays.

safety_player_name
  - Desc: Name of defender credited with forcing a safety.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null on non-safety plays.

lateral_sack_player_id
  - Desc: GSIS identifier of defender crediting a sack on a lateral play sequence.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null unless lateral sack occurred.

lateral_sack_player_name
  - Desc: Name of defender crediting a sack on a lateral play sequence.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null unless lateral sack occurred.

lateral_tackle_for_loss_player_id
  - Desc: GSIS identifier of defender crediting a TFL on a lateral play sequence.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null unless lateral TFL occurred.

lateral_tackle_for_loss_player_name
  - Desc: Name of defender crediting a TFL on a lateral play sequence.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null unless lateral TFL occurred.


15. FUMBLE TRACKING & RECOVERIES
--------------------------------------------------------------------------------
fumbled_1_team
  - Desc: Team abbreviation of the player who fumbled the ball (#1).
  - Data Type: String
  - Range / Values: Team abbreviation, null
  - Null Behavior: Null when fumble == 0.

fumbled_1_player_id
  - Desc: GSIS identifier of the player who fumbled the ball (#1).
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null when fumble == 0.

fumbled_1_player_name
  - Desc: Name of the player who fumbled the ball (#1).
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null when fumble == 0.

fumbled_2_team
  - Desc: Team abbreviation of the player who fumbled the ball (#2).
  - Data Type: String
  - Range / Values: Team abbreviation, null
  - Null Behavior: Null unless second fumble on play.

fumbled_2_player_id
  - Desc: GSIS identifier of the player who fumbled the ball (#2).
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null unless second fumble on play.

fumbled_2_player_name
  - Desc: Name of the player who fumbled the ball (#2).
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null unless second fumble on play.

fumble_recovery_1_team
  - Desc: Team abbreviation of the team recovering fumble #1.
  - Data Type: String
  - Range / Values: Team abbreviation, null
  - Null Behavior: Null when fumble == 0.

fumble_recovery_1_yards
  - Desc: Return distance in yards gained after recovering fumble #1.
  - Data Type: Float64
  - Range / Values: Float yards, null
  - Null Behavior: Null when fumble == 0.

fumble_recovery_1_player_id
  - Desc: GSIS identifier of the player who recovered fumble #1.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null when fumble == 0.

fumble_recovery_1_player_name
  - Desc: Name of the player who recovered fumble #1.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null when fumble == 0.

fumble_recovery_2_team
  - Desc: Team abbreviation of the team recovering fumble #2.
  - Data Type: String
  - Range / Values: Team abbreviation, null
  - Null Behavior: Null unless second fumble recovery.

fumble_recovery_2_yards
  - Desc: Return distance in yards gained after recovering fumble #2.
  - Data Type: Float64
  - Range / Values: Float yards, null
  - Null Behavior: Null unless second fumble recovery.

fumble_recovery_2_player_id
  - Desc: GSIS identifier of the player who recovered fumble #2.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null unless second fumble recovery.

fumble_recovery_2_player_name
  - Desc: Name of the player who recovered fumble #2.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null unless second fumble recovery.


16. KICKING & SPECIAL TEAMS ATTRIBUTION
--------------------------------------------------------------------------------
kicker_player_id
  - Desc: GSIS identifier of the kicker or punter executing the kick.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null on non-kick plays.

kicker_player_name
  - Desc: Name of the kicker or punter executing the kick.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null on non-kick plays.

kicker_id
  - Desc: Legacy kicker GSIS ID.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null on non-kick plays.

kicker_name
  - Desc: Legacy kicker name.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null on non-kick plays.

field_goal_result
  - Desc: Outcome classification of a field goal attempt.
  - Data Type: String
  - Range / Values: "made", "missed", "blocked", null
  - Null Behavior: Null on non-field goal plays.

kick_distance
  - Desc: Total distance in yards for a field goal, extra point, or kickoff.
  - Data Type: Float64
  - Range / Values: ~ 15.0 to 70.0
  - Null Behavior: Null on non-kick plays.

kick_distance_text
  - Desc: Text description of the kick distance length.
  - Data Type: String
  - Range / Values: Kick length description string, null
  - Null Behavior: Null on non-kick plays.

extra_point_result
  - Desc: Outcome classification of an extra point PAT kick attempt.
  - Data Type: String
  - Range / Values: "good", "failed", "blocked", null
  - Null Behavior: Null on non-PAT plays.

two_point_conv_result
  - Desc: Outcome classification of a 2-point conversion attempt.
  - Data Type: String
  - Range / Values: "success", "failure", null
  - Null Behavior: Null on non-2-point attempt plays.

punt_returner_player_id
  - Desc: GSIS identifier of the designated punt returner.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null on non-punt return plays.

punt_returner_player_name
  - Desc: Name of the designated punt returner.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null on non-punt return plays.

punt_returner_id
  - Desc: Legacy punt returner GSIS ID.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null on non-punt return plays.

punt_returner_name
  - Desc: Legacy punt returner name.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null on non-punt return plays.

kickoff_returner_player_id
  - Desc: GSIS identifier of the designated kickoff returner.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null on non-kickoff return plays.

kickoff_returner_player_name
  - Desc: Name of the designated kickoff returner.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null on non-kickoff return plays.

kickoff_returner_id
  - Desc: Legacy kickoff returner GSIS ID.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null on non-kickoff return plays.

kickoff_returner_name
  - Desc: Legacy kickoff returner name.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null on non-kickoff return plays.

punt_gained
  - Desc: Net yards gained or position shift resulting from a punt play.
  - Data Type: Float64
  - Range / Values: Net punt yards float, null
  - Null Behavior: Null on non-punt plays.

bid
  - Desc: GSIS player ID associated with a blocked kick event.
  - Data Type: String
  - Range / Values: Blocked kick player ID, null
  - Null Behavior: Null on non-blocked kick plays.

bid_team
  - Desc: Team abbreviation of the team blocking a kick.
  - Data Type: String
  - Range / Values: Team abbreviation, null
  - Null Behavior: Null on non-blocked kick plays.


17. PENALTIES, REPLAYS & GAME OFFICIALS
--------------------------------------------------------------------------------
penalty_team
  - Desc: Team abbreviation of the team penalized on the play.
  - Data Type: String
  - Range / Values: Team abbreviation, null
  - Null Behavior: Null on non-penalty plays.

penalty_player_id
  - Desc: GSIS identifier of the specific player penalized.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null on non-penalty plays.

penalty_player_name
  - Desc: Name of the specific player penalized.
  - Data Type: String
  - Range / Values: Name string, null
  - Null Behavior: Null on non-penalty plays.

penalty_yards
  - Desc: Total penalty yardage assessed by officials on the play.
  - Data Type: Float64
  - Range / Values: 0.0 to ~45.0
  - Null Behavior: 0.0 on non-penalty plays.

penalty_type
  - Desc: Official penalty violation rule description.
  - Data Type: String
  - Range / Values: Violation name (e.g., "Offensive Holding", "False Start")
  - Null Behavior: Null on non-penalty plays.

replay_or_challenge
  - Desc: Binary flag indicating if the play was subject to video replay review or coach challenge.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0
  - Null Behavior: 0.0 on standard plays.

replay_or_challenge_result
  - Desc: Ruling outcome of the video replay or challenge review.
  - Data Type: String
  - Range / Values: "upheld", "reversed", null
  - Null Behavior: Null on non-reviewed plays.

defensive_two_point_attempt
  - Desc: Binary flag indicating the defense attempted a turnover return on a 2-point try.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: Null on non-2-point plays.

defensive_two_point_conv
  - Desc: Binary flag indicating the defense successfully scored on a 2-point turnover return.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: Null on non-2-point plays.

defensive_extra_point_attempt
  - Desc: Binary flag indicating the defense attempted a return on a PAT kick.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: Null on non-PAT plays.

defensive_extra_point_conv
  - Desc: Binary flag indicating the defense successfully scored on a PAT return.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0, null
  - Null Behavior: Null on non-PAT plays.

referee
  - Desc: Full name of the head referee assigned to the game crew.
  - Data Type: String
  - Range / Values: Official name string, null
  - Null Behavior: Null on older historical feeds.

umpire
  - Desc: Full name of the umpire official assigned to the game crew.
  - Data Type: String
  - Range / Values: Official name string, null
  - Null Behavior: Null on older historical feeds.

head_linesman
  - Desc: Full name of the head linesman official assigned to the game crew.
  - Data Type: String
  - Range / Values: Official name string, null
  - Null Behavior: Null on older historical feeds.

line_judge
  - Desc: Full name of the line judge official assigned to the game crew.
  - Data Type: String
  - Range / Values: Official name string, null
  - Null Behavior: Null on older historical feeds.

back_judge
  - Desc: Full name of the back judge official assigned to the game crew.
  - Data Type: String
  - Range / Values: Official name string, null
  - Null Behavior: Null on older historical feeds.

side_judge
  - Desc: Full name of the side judge official assigned to the game crew.
  - Data Type: String
  - Range / Values: Official name string, null
  - Null Behavior: Null on older historical feeds.

field_judge
  - Desc: Full name of the field judge official assigned to the game crew.
  - Data Type: String
  - Range / Values: Official name string, null
  - Null Behavior: Null on older historical feeds.

replay_official
  - Desc: Full name of the replay booth official assigned to the game.
  - Data Type: String
  - Range / Values: Official name string, null
  - Null Behavior: Null on older historical feeds.


18. DRIVE & SERIES AGGREGATE METRICS
--------------------------------------------------------------------------------
drive
  - Desc: Sequential drive index number within the game.
  - Data Type: Float64
  - Range / Values: 1.0 to ~25.0
  - Null Behavior: Null on administrative plays.

fixed_drive
  - Desc: Standardized and cleaned drive sequence number in the game.
  - Data Type: Float64
  - Range / Values: 1.0 to ~25.0
  - Null Behavior: No nulls on scrimmage plays.

fixed_drive_result
  - Desc: Final outcome classification of the drive.
  - Data Type: String
  - Range / Values: "Touchdown", "Field goal", "Punt", "Turnover", "Safety", "End of half", etc.
  - Null Behavior: Null on administrative plays.

drive_real_start_time
  - Desc: Real-world clock timestamp when the drive initiated.
  - Data Type: String
  - Range / Values: Real-world timestamp string, null
  - Null Behavior: High null rate pre-2018.

drive_play_count
  - Desc: Total number of plays executed within the drive.
  - Data Type: Float64
  - Range / Values: 1.0 to ~20.0
  - Null Behavior: Null on non-drive plays.

drive_time_of_possession
  - Desc: Total duration of the drive formatted in minutes and seconds.
  - Data Type: String
  - Range / Values: "MM:SS"
  - Null Behavior: Null on non-drive plays.

drive_first_downs
  - Desc: Total number of first downs generated during the drive.
  - Data Type: Float64
  - Range / Values: 0.0 to ~10.0
  - Null Behavior: Null on non-drive plays.

drive_inside20
  - Desc: Binary flag indicating if the drive reached the opponent's 20-yard line (red zone).
  - Data Type: Float64
  - Range / Values: 0.0, 1.0
  - Null Behavior: 0.0 on standard drives.

drive_ended_with_score
  - Desc: Binary flag indicating if the drive resulted in points scored.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0
  - Null Behavior: 0.0 on non-scoring drives.

drive_quarter_start
  - Desc: Quarter during which the drive initiated.
  - Data Type: Float64
  - Range / Values: 1.0 to 5.0
  - Null Behavior: Null on non-drive plays.

drive_quarter_end
  - Desc: Quarter during which the drive concluded.
  - Data Type: Float64
  - Range / Values: 1.0 to 5.0
  - Null Behavior: Null on non-drive plays.

drive_yards_penalized
  - Desc: Net penalty yardage accrued during the drive.
  - Data Type: Float64
  - Range / Values: Penalized yards float
  - Null Behavior: 0.0 on non-penalized drives.

drive_start_transition
  - Desc: Play event or transition mode that started the possession drive.
  - Data Type: String
  - Range / Values: "KICKOFF", "PUNT", "FUMBLE", "INTERCEPTION", "DOWNS", etc.
  - Null Behavior: Null on non-drive plays.

drive_end_transition
  - Desc: Play event or transition mode that terminated the possession drive.
  - Data Type: String
  - Range / Values: "TOUCHDOWN", "FIELD_GOAL", "PUNT", "FUMBLE", etc.
  - Null Behavior: Null on non-drive plays.

drive_game_clock_start
  - Desc: Game clock time reading at the start of the drive.
  - Data Type: String
  - Range / Values: "15:00" to "00:00"
  - Null Behavior: Null on non-drive plays.

drive_game_clock_end
  - Desc: Game clock time reading at the conclusion of the drive.
  - Data Type: String
  - Range / Values: "15:00" to "00:00"
  - Null Behavior: Null on non-drive plays.

drive_start_yardline
  - Desc: Field position description where the drive started.
  - Data Type: String
  - Range / Values: e.g., "KC 25"
  - Null Behavior: Null on non-drive plays.

drive_end_yardline
  - Desc: Field position description where the drive ended.
  - Data Type: String
  - Range / Values: e.g., "BAL 10"
  - Null Behavior: Null on non-drive plays.

drive_play_id_started
  - Desc: Play ID of the first play executed in the drive.
  - Data Type: Float64
  - Range / Values: Play ID integer
  - Null Behavior: Null on non-drive plays.

drive_play_id_ended
  - Desc: Play ID of the final play executed in the drive.
  - Data Type: Float64
  - Range / Values: Play ID integer
  - Null Behavior: Null on non-drive plays.

series
  - Desc: Sequential 4-down series index within the drive.
  - Data Type: Float64
  - Range / Values: Sequential series integer
  - Null Behavior: Null on non-drive plays.

series_success
  - Desc: Binary flag indicating if the series resulted in a new first down or touchdown (1.0) vs turnover/punt (0.0).
  - Data Type: Float64
  - Range / Values: 0.0, 1.0
  - Null Behavior: Null on non-drive plays.

series_result
  - Desc: Outcome description of the 4-down series.
  - Data Type: String
  - Range / Values: "First down", "Touchdown", "Punt", "Turnover", etc.
  - Null Behavior: Null on non-drive plays.


19. MARKET BETTING LINES & ODDS METRICS
--------------------------------------------------------------------------------
spread_line
  - Desc: Closing point spread for the home team (+3.5 indicates home underdog by 3.5 points).
  - Data Type: Float64
  - Range / Values: ~ -27.0 to +27.0
  - Null Behavior: No nulls on modern games.

total_line
  - Desc: Closing game over/under total combined points line.
  - Data Type: Float64
  - Range / Values: ~ 30.0 to 65.0
  - Null Behavior: No nulls on modern games.

home_moneyline
  - Desc: Closing American moneyline odds price for the home team.
  - Data Type: Float64
  - Range / Values: American odds integer (e.g., -150, +130)
  - Null Behavior: Null in older feeds.

away_moneyline
  - Desc: Closing American moneyline odds price for the visiting team.
  - Data Type: Float64
  - Range / Values: American odds integer (e.g., +130, -150)
  - Null Behavior: Null in older feeds.

home_spread_probability
  - Desc: Implied probability of the home team covering the point spread derived from market odds.
  - Data Type: Float64
  - Range / Values: Implied probability (0.0 to 1.0)
  - Null Behavior: Null in older feeds.

away_spread_probability
  - Desc: Implied probability of the visiting team covering the point spread derived from market odds.
  - Data Type: Float64
  - Range / Values: Implied probability (0.0 to 1.0)
  - Null Behavior: Null in older feeds.

home_spread_odds
  - Desc: Closing American odds for betting on the home team spread.
  - Data Type: Float64
  - Range / Values: American odds (e.g., -110)
  - Null Behavior: Null in older feeds.

away_spread_odds
  - Desc: Closing American odds for betting on the visiting team spread.
  - Data Type: Float64
  - Range / Values: American odds (e.g., -110)
  - Null Behavior: Null in older feeds.

home_favorite
  - Desc: Binary flag indicating if the home team was favoured by betting markets.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0
  - Null Behavior: No nulls on modern games.

away_favorite
  - Desc: Binary flag indicating if the visiting team was favoured by betting markets.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0
  - Null Behavior: No nulls on modern games.

total_line_odds_over
  - Desc: Closing American odds for betting the Over on total points.
  - Data Type: Float64
  - Range / Values: American odds (e.g., -110)
  - Null Behavior: Null in older feeds.

total_line_odds_under
  - Desc: Closing American odds for betting the Under on total points.
  - Data Type: Float64
  - Range / Values: American odds (e.g., -110)
  - Null Behavior: Null in older feeds.

result
  - Desc: Final game point differential relative to the home team (home_score - away_score).
  - Data Type: Float64
  - Range / Values: Integer differential
  - Null Behavior: No nulls on completed game rows.

total
  - Desc: Final game combined score total (home_score + away_score).
  - Data Type: Float64
  - Range / Values: Combined points float
  - Null Behavior: No nulls on completed game rows.

spread_covered
  - Desc: Binary flag indicating if the home team covered the closing point spread.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0
  - Null Behavior: No nulls on completed game rows.

total_covered
  - Desc: Binary flag indicating if the combined score exceeded the closing over/under line.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0
  - Null Behavior: No nulls on completed game rows.


20. STADIUM & ENVIRONMENTAL CONDITIONS
--------------------------------------------------------------------------------
roof
  - Desc: Categorical classification of the stadium roof setup.
  - Data Type: String
  - Range / Values: "outdoors", "dome", "closed", "open", null
  - Null Behavior: Null on older games.

roof_type
  - Desc: Explicit stadium roof construction type.
  - Data Type: String
  - Range / Values: "outdoors", "dome", "closed", "open"
  - Null Behavior: No nulls on modern games.

is_roof_open
  - Desc: Binary flag indicating if a retractable roof stadium had its roof open during play.
  - Data Type: Float64
  - Range / Values: 0.0, 1.0
  - Null Behavior: 0.0 for domes/outdoors.

surface
  - Desc: Specific playing surface field material installed at the venue.
  - Data Type: String
  - Range / Values: "grass", "fieldturf", "astroturf", "a_turf", "matrix", etc.
  - Null Behavior: No nulls on valid game rows.

surface_type
  - Desc: Simplified binary classification of playing surface.
  - Data Type: String
  - Range / Values: "grass", "turf"
  - Null Behavior: No nulls on valid game rows.

temp
  - Desc: Outdoor air temperature reading at kickoff in degrees Fahrenheit.
  - Data Type: Float64
  - Range / Values: ~ -10 to 110 (°F)
  - Null Behavior: Null for domes or unrecorded games.

weather_temperature
  - Desc: Alternate outdoor temperature measurement field.
  - Data Type: Float64
  - Range / Values: Temperature in °F
  - Null Behavior: Null for indoor games.

wind
  - Desc: Outdoor wind speed velocity measurement at kickoff in miles per hour.
  - Data Type: Float64
  - Range / Values: 0 to ~50 (mph)
  - Null Behavior: Null for domes.

weather_wind_mph
  - Desc: Alternate wind velocity measurement field.
  - Data Type: Float64
  - Range / Values: Wind speed in mph
  - Null Behavior: Null for indoor games.

weather_humidity
  - Desc: Relative atmospheric humidity percentage recorded at kickoff.
  - Data Type: Float64
  - Range / Values: 0 to 100 (%)
  - Null Behavior: Sparse in older feeds.

weather
  - Desc: Unparsed raw weather report text string from the game report.
  - Data Type: String
  - Range / Values: Text weather string
  - Null Behavior: Null for domes.

weather_detail
  - Desc: Categorical weather condition summary (e.g., "Rain", "Snow", "Clear").
  - Data Type: String
  - Range / Values: Detailed weather string
  - Null Behavior: Null for domes.

stadium
  - Desc: Full official name of the stadium venue.
  - Data Type: String
  - Range / Values: Stadium name string
  - Null Behavior: No nulls on valid game rows.

stadium_id
  - Desc: Unique venue identification code.
  - Data Type: String
  - Range / Values: Venue code string
  - Null Behavior: No nulls on valid game rows.

game_stadium
  - Desc: Alternate field for official stadium name.
  - Data Type: String
  - Range / Values: Stadium name string
  - Null Behavior: No nulls on valid game rows.

game_stadium_id
  - Desc: Alternate field for unique stadium ID.
  - Data Type: String
  - Range / Values: Venue code string
  - Null Behavior: No nulls on valid game rows.


21. FANTASY & GENERAL PLAYER IDENTIFIERS
--------------------------------------------------------------------------------
fantasy_player_name
  - Desc: Primary skill player name associated with the play for fantasy point attribution.
  - Data Type: String
  - Range / Values: Player name string, null
  - Null Behavior: Null on non-skill plays.

fantasy_player_id
  - Desc: Unique GSIS identifier of the primary fantasy skill player.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null on non-skill plays.

fantasy
  - Desc: Alternate field for primary fantasy skill player name.
  - Data Type: String
  - Range / Values: Player name string, null
  - Null Behavior: Null on non-skill plays.

fantasy_id
  - Desc: Alternate field for primary fantasy skill player GSIS ID.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null on non-skill plays.

jersey_number
  - Desc: Uniform jersey number worn by the primary player involved in the play.
  - Data Type: Float64
  - Range / Values: 0 to 99
  - Null Behavior: Null on administrative plays.

id
  - Desc: Generic GSIS player ID attributed to the primary play event.
  - Data Type: String
  - Range / Values: GSIS ID string, null
  - Null Behavior: Null on administrative plays.

name
  - Desc: Generic player name attributed to the primary play event.
  - Data Type: String
  - Range / Values: Player name string, null
  - Null Behavior: Null on administrative plays.
================================================================================
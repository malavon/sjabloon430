--
-- File generated with SQLiteStudio.
--
-- Text encoding used: UTF-8
--

-- Table: signal
CREATE TABLE IF NOT EXISTS signal (
    id            TEXT PRIMARY KEY ON CONFLICT ROLLBACK
                       NOT NULL,
    desc          TEXT NOT NULL,
    feature_group TEXT REFERENCES feature (signal_group)
)
STRICT;

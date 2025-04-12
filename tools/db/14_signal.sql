--
-- File generated with SQLiteStudio, comment modified manually!
--
-- Text encoding used: UTF-8
--

-- Table: signal
CREATE TABLE IF NOT EXISTS signal (
    id            TEXT PRIMARY KEY ON CONFLICT ROLLBACK
                       NOT NULL,
    desc          TEXT NOT NULL,
    feature_group TEXT CONSTRAINT FK_SIGNAL_FEATURE REFERENCES feature (signal_group) 
)
STRICT;

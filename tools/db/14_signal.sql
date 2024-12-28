--
-- File generated with SQLiteStudio, comment modified manually!
--
-- Text encoding used: UTF-8
--

-- Table: signal
CREATE TABLE IF NOT EXISTS signal (
    id                   INTEGER PRIMARY KEY ON CONFLICT ROLLBACK AUTOINCREMENT
                                 NOT NULL,
    signal_name          TEXT    NOT NULL,
    signal_desc          TEXT    NOT NULL,
    signal_feature_group TEXT    CONSTRAINT FK_SIGNAL_FEATURE REFERENCES feature (signal_group) 
)
STRICT;

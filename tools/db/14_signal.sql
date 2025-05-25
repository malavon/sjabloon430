--
-- File generated with SQLiteStudio.
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

-- Table: package_signal
CREATE TABLE IF NOT EXISTS package_signal (
    package_id  INTEGER REFERENCES package (id) ON DELETE RESTRICT
                        NOT NULL,
    signal_id   INTEGER NOT NULL
                        REFERENCES signal (id) ON DELETE RESTRICT
                                               ON UPDATE RESTRICT,
    pin_row_bga TEXT,
    pin_number  INTEGER NOT NULL,
    is_default  INTEGER DEFAULT (0) 
                        NOT NULL,
    comment     TEXT,
    CONSTRAINT PK_PACKAGE_SIGNAL PRIMARY KEY (
        package_id,
        signal_id
    )
    ON CONFLICT FAIL
)
WITHOUT ROWID,
STRICT;


--
-- File generated with SQLiteStudio.
--
-- Text encoding used: UTF-8
--

-- Table: pinset
CREATE TABLE IF NOT EXISTS pinset (
    id            INTEGER PRIMARY KEY AUTOINCREMENT,
    parent_id     INTEGER REFERENCES pinset (id) ON DELETE RESTRICT
                                                 ON UPDATE CASCADE,
    pins          INTEGER NOT NULL,
    comment       TEXT
)
STRICT;

-- Table: pinset_signal
CREATE TABLE IF NOT EXISTS pinset_signal (
    pinset_id   INTEGER NOT NULL
                        REFERENCES pinset (id) ON DELETE RESTRICT
                                               ON UPDATE CASCADE,
    signal_id   TEXT    NOT NULL
                        REFERENCES signal (id) ON DELETE RESTRICT
                                               ON UPDATE CASCADE,
    idx         INTEGER NOT NULL,
    pin_row_bga TEXT,
    pin_number  INTEGER NOT NULL,
    comment     TEXT,
    CONSTRAINT PK_PACKAGE_SIGNAL PRIMARY KEY (
        pinset_id,
        signal_id
    )
    ON CONFLICT FAIL,
    CONSTRAINT UQ_SIGNAL_SET_PK_INDEX UNIQUE (
        pinset_id,
        signal_id,
        idx ASC
    )
    ON CONFLICT ROLLBACK
)
WITHOUT ROWID,
STRICT;

--
-- File generated with SQLiteStudio, comment modified manually!
--
-- Text encoding used: UTF-8
--

-- Table: pinset_signal
CREATE TABLE IF NOT EXISTS pinset_signal (
    pinset_id   INTEGER REFERENCES pinset (id) ON DELETE RESTRICT
                        NOT NULL,
    signal_id   TEXT    NOT NULL
                        REFERENCES signal (id) ON DELETE RESTRICT
                                               ON UPDATE RESTRICT,
    idx         INTEGER CONSTRAINT NN_SIGNAL_SET_INDEX NOT NULL,
    pin_row_bga TEXT,
    pin_number  INTEGER CONSTRAINT NN_SIGNAL_PINSET_PIN_NUMER NOT NULL,
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

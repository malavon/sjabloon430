--
-- File generated with SQLiteStudio v3.4.4
--
-- Text encoding used: UTF-8
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: datasheet
CREATE TABLE IF NOT EXISTS datasheet (
    id          TEXT    PRIMARY KEY ON CONFLICT ROLLBACK,
    revision    TEXT,
    issue_month INTEGER NOT NULL,
    issue_year  INTEGER NOT NULL,
    rev_month   INTEGER NOT NULL,
    rev_year    INTEGER NOT NULL,
    comment     TEXT
)
WITHOUT ROWID,
STRICT;


-- Table: device
CREATE TABLE IF NOT EXISTS device (
    id            INTEGER PRIMARY KEY ON CONFLICT ROLLBACK AUTOINCREMENT
                          NOT NULL,
    datasheet_id  TEXT    REFERENCES datasheet (id) ON DELETE RESTRICT
                          NOT NULL,
    model         TEXT    NOT NULL
                          UNIQUE,
    freq_max      INTEGER,
    storage_bytes INTEGER,
    ram_bytes     INTEGER,
    gpio_count    INTEGER,
    uart_count    INTEGER,
    usb_count     INTEGER DEFAULT (0),
    i2c_count     INTEGER,
    spi_count     INTEGER,
    comp_count    INTEGER,
    timer_count   INTEGER,
    op_temp_min   INTEGER,
    op_temp_max   INTEGER,
    comment       TEXT
)
STRICT;


-- Table: device_feature
CREATE TABLE IF NOT EXISTS device_feature (
    device_id  INTEGER REFERENCES device (id) ON DELETE RESTRICT
                       NOT NULL,
    feature_id TEXT    REFERENCES feature (id) ON DELETE RESTRICT
                       NOT NULL,
    param1     ANY,
    param2     ANY,
    param3     ANY,
    comment    TEXT
)
STRICT;


-- Table: feature
CREATE TABLE IF NOT EXISTS feature (
    id                 TEXT PRIMARY KEY,
    param1_description TEXT,
    param2_description ANY,
    param3_description ANY,
    comment            TEXT,
    family_text        TEXT,
    family_group       TEXT
)
WITHOUT ROWID,
STRICT;


COMMIT TRANSACTION;
PRAGMA foreign_keys = on;

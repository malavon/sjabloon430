--
-- File generated with SQLiteStudio, comment modified manually!
--
-- Text encoding used: UTF-8
--

-- Table: package
CREATE TABLE IF NOT EXISTS package (
    id        INTEGER PRIMARY KEY ON CONFLICT ROLLBACK AUTOINCREMENT
                      NOT NULL,
    device_id INTEGER REFERENCES device (id) ON DELETE CASCADE,
    type      TEXT    NOT NULL,
    drawing   TEXT    NOT NULL,
    pins      INTEGER NOT NULL,
    comment   TEXT,
    CONSTRAINT UQ_PACKAGE_DEV_DRW_PINS UNIQUE (
        device_id,
        drawing,
        pins
    )
    ON CONFLICT ROLLBACK
)
STRICT;

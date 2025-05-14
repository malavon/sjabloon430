--
-- File generated with SQLiteStudio.
--
-- Text encoding used: UTF-8
--

-- Table: signalgroup
CREATE TABLE IF NOT EXISTS signalgroup (
    name TEXT PRIMARY KEY
);

-- Table: signal
CREATE TABLE IF NOT EXISTS signal (
    id          TEXT PRIMARY KEY ON CONFLICT ROLLBACK
                     NOT NULL,
    desc        TEXT NOT NULL,
    signalgroup TEXT REFERENCES signalgroup (name) 
)
STRICT;

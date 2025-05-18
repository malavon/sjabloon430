
-- SIMPLE TEST to indicate if current tables are workable
-- and to implement the code to insert pinsets eventually
-- view + add signals first
-- then insert pinsets

BEGIN TRANSACTION;



-- MSP430G2113 doesn't have a separate device and is linked to MSP430G2153 which is wrong
-- either add MSP430G2113 as separate device, or remove it
-- in SLAS735 there is no more information, exception a single orderable which is still available
-- note: revision J has been modified since 2017 ...

-- DELETE FROM orderable WHERE name = 'MSP430G2113IN20';
-- 
-- INSERT INTO pinset (id, pins, parent_set_id) VALUES (1, 20, NULL);
-- INSERT INTO pinset (id, pins, parent_set_id) VALUES (2, 20, 1);
-- 
-- UPDATE orderable
-- SET pinset_id = 1
-- WHERE device_id IN (
--     SELECT DISTINCT device_id
--     FROM device d
--     INNER JOIN orderable o ON o.device_id = d.id
--     WHERE d.datasheet_id = 'SLAS735' AND
--           d.model LIKE '%13'
-- );
-- 
-- UPDATE orderable-- incorrect: MSP430G2113 also gets pinset 2: orderable without correct device (no longer in datasheet...)
-- SET pinset_id = 2
-- WHERE device_id IN (
--     SELECT DISTINCT device_id
--     FROM device d
--     INNER JOIN orderable o ON o.device_id = d.id
--     WHERE d.datasheet_id = 'SLAS735' AND
--           d.model LIKE '%53'
-- );
-- 
COMMIT TRANSACTION;

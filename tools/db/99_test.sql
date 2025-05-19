--
-- File generated with one of the sjabloon 430 database tools.
-- Any alterations to this data will be kept by these tools, assuming the SQL is still valid.
-- DO NOT REFORMAT THIS FILE AND CHECK IN ONLY AFTER RE-EXPORTING WITH A SJABLOON 430 TOOL.
--
-- Text encoding used: UTF-8
--
/*
BEGIN TRANSACTION;
-- GENERATED FROM HERE
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (1, NULL, 0);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (2, NULL, 1);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (3, NULL, 2);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (4, NULL, 3);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (5, NULL, 4);

-- TODO: order idx before signal_id; also order by idx!
-- TODO: also at least this query can be considerably simpler, check output first!
INSERT INTO signalset_signal (signalset_id, signal_id, idx) VALUES (1, 'NMI', 1);
INSERT INTO signalset_signal (signalset_id, signal_id, idx) VALUES (1, 'SBWTDIO', 2);
INSERT INTO signalset_signal (signalset_id, signal_id, idx) VALUES (1, '~RST', 0);
INSERT INTO signalset_signal (signalset_id, signal_id, idx) VALUES (2, 'SBWTCK', 1);
INSERT INTO signalset_signal (signalset_id, signal_id, idx) VALUES (2, 'TEST', 0);
INSERT INTO signalset_signal (signalset_id, signal_id, idx) VALUES (3, 'A4', 5);
INSERT INTO signalset_signal (signalset_id, signal_id, idx) VALUES (3, 'P1.4', 0);
INSERT INTO signalset_signal (signalset_id, signal_id, idx) VALUES (3, 'TA1.2', 3);
INSERT INTO signalset_signal (signalset_id, signal_id, idx) VALUES (3, 'TCK', 4);
INSERT INTO signalset_signal (signalset_id, signal_id, idx) VALUES (3, 'UCA0SIMO', 2);
INSERT INTO signalset_signal (signalset_id, signal_id, idx) VALUES (3, 'UCA0TXDG', 1);
INSERT INTO signalset_signal (signalset_id, signal_id, idx) VALUES (3, 'VREF+', 6);
INSERT INTO signalset_signal (signalset_id, signal_id, idx) VALUES (4, 'A5', 5);
INSERT INTO signalset_signal (signalset_id, signal_id, idx) VALUES (4, 'P1.5', 0);
INSERT INTO signalset_signal (signalset_id, signal_id, idx) VALUES (4, 'TA1.1', 3);
INSERT INTO signalset_signal (signalset_id, signal_id, idx) VALUES (4, 'TMS', 4);
INSERT INTO signalset_signal (signalset_id, signal_id, idx) VALUES (4, 'UCA0RXD', 1);
INSERT INTO signalset_signal (signalset_id, signal_id, idx) VALUES (4, 'UCA0SOMI', 2);
INSERT INTO signalset_signal (signalset_id, signal_id, idx) VALUES (5, 'A6', 5);
INSERT INTO signalset_signal (signalset_id, signal_id, idx) VALUES (5, 'P1.6', 0);
INSERT INTO signalset_signal (signalset_id, signal_id, idx) VALUES (5, 'TA1CLK', 2);
INSERT INTO signalset_signal (signalset_id, signal_id, idx) VALUES (5, 'TCLK', 4);
INSERT INTO signalset_signal (signalset_id, signal_id, idx) VALUES (5, 'TDI', 3);
INSERT INTO signalset_signal (signalset_id, signal_id, idx) VALUES (5, 'UCA0CLK', 1);

INSERT INTO pinset (id, pins, comment) VALUES (1, 5, NULL);
INSERT INTO pinset (id, pins, comment) VALUES (2, 5, NULL);
INSERT INTO pinset (id, pins, comment) VALUES (3, 5, NULL);
INSERT INTO pinset (id, pins, comment) VALUES (4, 5, NULL);

INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (1, 1, NULL, '1');
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (1, 2, NULL, '2');
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (1, 3, NULL, '3');
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (1, 4, NULL, '4');
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (1, 5, NULL, '5');
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (2, 1, NULL, '5');
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (2, 2, NULL, '6');
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (2, 3, NULL, '7');
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (2, 4, NULL, '8');
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (2, 5, NULL, '9');
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (3, 1, NULL, '1');
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (3, 2, NULL, '2');
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (3, 3, NULL, '3');
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (3, 4, NULL, '4');
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (3, 5, NULL, '5');
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (4, 1, 'E', '1');
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (4, 2, 'D', '2');
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (4, 3, 'D', '1');
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (4, 4, 'C', '2');
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (4, 5, 'C', '3');
-- THESE ARE MANUAL FOR NOW!!!
UPDATE orderable SET pinset_id = 1 WHERE drawing = 'RHB' AND pins = 32 AND device_id IN (SELECT model FROM device d WHERE datasheet_id = 'SLAS942');
UPDATE orderable SET pinset_id = 2 WHERE drawing = 'DA'  AND pins = 32 AND device_id IN (SELECT model FROM device d WHERE datasheet_id = 'SLAS942');
UPDATE orderable SET pinset_id = 3 WHERE drawing = 'RGE' AND pins = 24 AND device_id IN (SELECT model FROM device d WHERE datasheet_id = 'SLAS942');
UPDATE orderable SET pinset_id = 4 WHERE drawing = 'YQW' AND pins = 24 AND device_id IN (SELECT model FROM device d WHERE datasheet_id = 'SLAS942');

COMMIT TRANSACTION;
*/

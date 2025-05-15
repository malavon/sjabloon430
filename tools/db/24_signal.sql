--
-- File generated with one of the sjabloon 430 database tools.
-- Any alterations to this data will be kept by these tools, assuming the SQL is still valid.
-- DO NOT REFORMAT THIS FILE AND CHECK IN ONLY AFTER RE-EXPORTING WITH A SJABLOON 430 TOOL.
--
-- Text encoding used: UTF-8
--
BEGIN TRANSACTION;

INSERT INTO signal (id, desc, signal_group) VALUES ('A0', 'Analog input A0', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('A1', 'Analog input A1', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('A2', 'Analog input A2', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('A3', 'Analog input A3', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('A4', 'Analog input A4', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('A5', 'Analog input A5', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('A6', 'Analog input A6', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('A7', 'Analog input A7', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('CAP0.0', 'CapTIvate channel', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('CAP0.1', 'CapTIvate channel', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('CAP0.2', 'CapTIvate channel', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('CAP0.3', 'CapTIvate channel', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('CAP1.0', 'CapTIvate channel', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('CAP1.1', 'CapTIvate channel', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('CAP1.2', 'CapTIvate channel', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('CAP1.3', 'CapTIvate channel', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('CAP2.0', 'CapTIvate channel', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('CAP2.1', 'CapTIvate channel', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('CAP2.2', 'CapTIvate channel', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('CAP2.3', 'CapTIvate channel', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('CAP3.0', 'CapTIvate channel', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('CAP3.1', 'CapTIvate channel', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('CAP3.2', 'CapTIvate channel', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('CAP3.3', 'CapTIvate channel', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('NMI', 'Nonmaskable interrupt input', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('SBWTCK', 'Spy-Bi-Wire input clock', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('SBWTDIO', 'Spy-Bi-Wire data input/output', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('SYNC', 'CapTIvate synchronous ...', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('TEST', 'Test Mode pin', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('Veref+', 'ADC positive reference', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('Veref-', 'ADC negative reference', NULL);
INSERT INTO signal (id, desc, signal_group) VALUES ('~RST', 'Active-low reset input', NULL);

COMMIT TRANSACTION;

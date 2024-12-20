--
-- File generated with SQLiteStudio, comment modified manually!
--
-- Text encoding used: UTF-8
--

BEGIN TRANSACTION;

INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('ADC_SAR10', 'External channels', 'Internal channels', NULL, '10-bit SAR ADC', '10-bit SAR', 'ADC');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('ADC_SAR12', 'External channels', 'Internal channels', NULL, '12-bit SAR ADC', '12-bit SAR', 'ADC');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('ADC_SD16', 'External channels', 'Internal channels', NULL, '16-bit Sigma Delta ADC', '16-bit Sigma Delta', 'ADC');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('ADC_SD24', 'External channels', 'Internal channels', NULL, '24-bit Sigma Delta ADC', '24-bit Sigma Delta', 'ADC');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('ADC_SLOPE', NULL, NULL, NULL, 'Slope ADC', 'Slope', 'ADC');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('ADV_SENSE', NULL, NULL, NULL, 'Included in TI export as feature', 'Advanced sensing', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('AES', NULL, NULL, NULL, 'AES Encryption/Decryption', 'AES', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('AFE', 'TODO', NULL, NULL, '??', 'Ultrasonic sensing AFE', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('BOD', NULL, NULL, NULL, 'Brownout Detect', 'Brown out detector', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('BOR', NULL, NULL, NULL, 'Brownout Reset', 'Brown out reset', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('BSL_I2C', NULL, NULL, NULL, 'Bootloader I²C version', 'I2C', 'BSL');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('BSL_UART', NULL, NULL, NULL, 'Bootloader UART version', 'UART', 'BSL');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('BSL_USB', NULL, NULL, NULL, 'Bootlloader USB version', 'USB', 'BSL');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('DIRECT', NULL, NULL, NULL, 'Included in TI export as feature', 'Direct drive', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('DMA', NULL, NULL, NULL, 'Direct Memory Access', 'DMA', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('HW_MUL32', NULL, NULL, NULL, NULL, '32-bit hardware multiplier', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('IGNORE_5V_IOS', NULL, NULL, NULL, 'Included in TI export as feature', '5-V-tolerant I/Os', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('IGNORE_BSL', NULL, NULL, NULL, 'Included in TI export as feature', 'Bootstrap loader', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('IGNORE_SD', '? not certain ignore', NULL, NULL, 'Included in TI export as feature', 'Sigma delta', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('IO_1.8V', NULL, NULL, NULL, NULL, '1.8V I/O', 'Special I/O');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('IO_5.0V_TOL', NULL, NULL, NULL, NULL, '5V Tolerant I/O', 'Special I/O');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('IO_CAPTIVATE', NULL, NULL, NULL, NULL, 'CapTIvate Touch I/O', 'Special I/O');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('IRML', 'TODO? part of USCI too?', NULL, NULL, '??', 'IR Modulation Logic', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('LCD', 'Type (A-E)', '# Common', '# Elements', 'LCD ontroller', 'LCD', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('LEA', NULL, NULL, NULL, '??', 'Low-energy accelerator (LEA)', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('MTIF', NULL, NULL, NULL, '??', 'Metering test interface (MTIF)', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('OP_AMP', NULL, NULL, NULL, '??', 'OpAmp', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('PGA', NULL, NULL, NULL, '??', 'PGA', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('RTC', NULL, NULL, NULL, 'Real-time clock', NULL, 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('SAC_DAC', NULL, NULL, NULL, 'SAC DAC?', 'DAC', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('SCAN', NULL, NULL, NULL, '??', 'Scan interface', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('SPY_WIRE', NULL, NULL, NULL, '??', 'Spy-bi-wire', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('TEMP_SENSOR', NULL, NULL, NULL, 'Temperature Sensor', 'Temp sensor', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('TRANS_AMP', 'TODO', NULL, NULL, '??', 'Transimpedance amplifier', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('USCI_A', 'TODO: not all IrDA? all LIn?', NULL, NULL, 'USCI with IrDA, UART, SPI', NULL, NULL);
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('USCI_A_LIN', 'TODO: not all IrDA?', NULL, NULL, 'USCI with IrDA, UART, SPI', NULL, NULL);
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('USCI_B', NULL, NULL, NULL, 'USCI with I²C, SPI', NULL, NULL);
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('WTD+', NULL, NULL, NULL, NULL, 'Watchdog timer', 'Features');

COMMIT TRANSACTION;

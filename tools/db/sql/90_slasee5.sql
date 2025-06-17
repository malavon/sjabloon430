--
-- File generated with one of the sjabloon 430 database tools.
-- Any alterations to this data will be kept by these tools, assuming the SQL is still valid.
-- DO NOT REFORMAT THIS FILE AND CHECK IN ONLY AFTER RE-EXPORTING WITH A SJABLOON 430 TOOL.
--
-- Text encoding used: UTF-8
--
BEGIN TRANSACTION;

INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2422', 'SLASEE5', 16, 8192, 2048, 15, 1, 0, 1, 2, 0, 2, -40, 85, 'TI EXPORT');

INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR2422', 'ADC_SAR10', '8', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR2422', 'BSL_I2C', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');

INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2422IPW16' , 'MSP430FR2422', 'PW' ,  16, 'ACTIVE', 2, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2422IPW16R', 'MSP430FR2422', 'PW' ,  16, 'ACTIVE', 2, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2422IRHLR' , 'MSP430FR2422', 'RHL',  20, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2422IRHLT' , 'MSP430FR2422', 'RHL',  20, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');

INSERT INTO pinset (id, parent_id, pins, comment) VALUES (  11, NULL,  16, NULL);
INSERT INTO pinset (id, parent_id, pins, comment) VALUES (  12, NULL,  20, NULL);

INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (   73,  NULL,   0);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (   74,  NULL,   1);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (   75,  NULL,   2);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (   76,  NULL,   3);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (   77,  NULL,   4);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (   78,  NULL,   5);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (   79,  NULL,   6);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (   80,  NULL,   7);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (   81,  NULL,   8);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (   82,  NULL,   9);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (   83,  NULL,  10);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (   84,  NULL,  11);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (   85,  NULL,  12);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (   86,  NULL,  13);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (   87,  NULL,  14);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (   88,  NULL,  15);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (   89,  NULL,  16);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (   90,  NULL,  17);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (   91,  NULL,  18);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (   92,  NULL,  19);

INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  11,    73, NULL,   1);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  12,    73, NULL,   1);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  11,    74, NULL,   2);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  12,    74, NULL,   2);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  11,    75, NULL,   3);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  12,    75, NULL,   3);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  11,    76, NULL,   4);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  12,    76, NULL,   4);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  11,    77, NULL,   5);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  12,    77, NULL,   5);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  11,    78, NULL,   6);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  12,    78, NULL,   6);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  11,    79, NULL,   7);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  12,    79, NULL,   7);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  11,    80, NULL,   8);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  12,    80, NULL,   8);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  12,    81, NULL,   9);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  12,    82, NULL,  10);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  12,    83, NULL,  11);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  12,    84, NULL,  12);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  11,    85, NULL,   9);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  12,    85, NULL,  13);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  11,    86, NULL,  10);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  12,    86, NULL,  14);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  11,    87, NULL,  11);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  12,    87, NULL,  15);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  11,    88, NULL,  12);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  12,    88, NULL,  16);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  11,    89, NULL,  13);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  12,    89, NULL,  17);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  11,    90, NULL,  14);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  12,    90, NULL,  18);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  11,    91, NULL,  15);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  12,    91, NULL,  19);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  11,    92, NULL,  16);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (  12,    92, NULL,  20);

INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   73, 0, 'P1.1'     );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   73, 1, 'UCB0CLK'  );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   73, 2, 'ACLK'     );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   73, 3, 'A1'       );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   73, 4, 'VREF+'    );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   74, 0, 'P1.0'     );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   74, 1, 'UCB0STE'  );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   74, 2, 'A0'       );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   74, 3, 'VEREF+'   );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   75, 0, 'TEST'     );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   75, 1, 'SBWTCK'   );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   76, 0, '~RST'     );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   76, 1, 'NMI'      );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   76, 2, 'SBWTDIO'  );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   77, 0, 'DVCC'     );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   78, 0, 'DVSS'     );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   79, 0, 'P1.2'     );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   79, 1, 'UCA0RXD'  );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   79, 2, 'UCA0SOMI' );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   79, 3, 'XIN'      );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   80, 0, 'P2.0'     );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   80, 1, 'UCA0TXD'  );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   80, 2, 'UCA0SIMO' );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   80, 3, 'XOUT'     );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   81, 0, 'P2.6'     );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   81, 1, 'UCB0SOMI' );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   81, 2, 'UCB0SCL'  );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   82, 0, 'P2.5'     );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   82, 1, 'UCB0SIMO' );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   82, 2, 'UCB0SDA'  );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   82, 3, 'A7'       );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   83, 0, 'P2.4'     );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   83, 1, 'TA1CLK'   );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   83, 2, 'UCB0CLK'  );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   83, 3, 'A6'       );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   84, 0, 'P2.3'     );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   84, 1, 'TA1.2'    );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   84, 2, 'UCB0STE'  );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   84, 3, 'A5'       );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   85, 0, 'P2.2'     );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   85, 1, 'TA1.1'    );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   85, 2, 'A4'       );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   86, 0, 'P1.7'     );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   86, 1, 'UCA0STE'  );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   86, 2, 'TDO'      );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   87, 0, 'P1.6'     );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   87, 1, 'UCA0CLK'  );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   87, 2, 'TA0CLK'   );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   87, 3, 'TDI'      );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   87, 4, 'TCLK'     );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   88, 0, 'P1.5'     );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   88, 1, 'UCA0RXD'  );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   88, 2, 'UCA0SOMI' );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   88, 3, 'TA0.2'    );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   88, 4, 'TMS'      );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   88, 5, 'BSL_RX'   );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   89, 0, 'P1.4'     );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   89, 1, 'UCA0TXD'  );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   89, 2, 'UCA0SIMO' );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   89, 3, 'TA0.1'    );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   89, 4, 'TCK'      );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   89, 5, 'BSL_TX'   );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   90, 0, 'DNC'      );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   91, 0, 'P1.3'     );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   91, 1, 'UCB0SOMI' );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   91, 2, 'UCB0SCL'  );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   91, 3, 'MCLK'     );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   91, 4, 'A3'       );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   91, 5, 'BSL_SCL'  );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   92, 0, 'P1.2'     );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   92, 1, 'UCB0SIMO' );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   92, 2, 'UCB0SDA'  );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   92, 3, 'SMCLK'    );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   92, 4, 'A2'       );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   92, 5, 'VEREF-'   );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (   92, 6, 'BSL_SDA'  );

UPDATE orderable SET pinset_id =   11 WHERE name = 'MSP430FR2422IPW16';
UPDATE orderable SET pinset_id =   11 WHERE name = 'MSP430FR2422IPW16R';
UPDATE orderable SET pinset_id =   12 WHERE name = 'MSP430FR2422IRHLR';
UPDATE orderable SET pinset_id =   12 WHERE name = 'MSP430FR2422IRHLT';

COMMIT TRANSACTION;

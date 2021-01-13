# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import sys
from PersistenceLayer.Repository import repo

def database_building(database_records_as_strings):
    database_records = None
    for i in range(database_records_as_strings.count):
        database_records.insert(database_records_as_strings[i].split(','))
    repo.create_tables()
    repo.store(database_records)
    pass


def manage_orders(orders):
    for i in range(orders.count):
        record = orders[i].split(',')
        if record.count == 2:
            repo.send_shipment(record[0], record[1])
        elif record.count == 3:
            repo.receive_shipment(record[0], record[1], record[2])

def main(config_file, orders_file, output_file):
    with open(config_file,"r",encode="utf-8") as cfile:
        lines = cfile.readlines()
        database_building(lines)
    with open(orders_file,"r",encode="utf-8") as ofile:
        lines = ofile.readlines()
        manage_orders(lines)
    pass

if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2], sys.argv[3])
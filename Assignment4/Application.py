# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
#import sys
from PersistenceLayer import Repository

def database_building(database_records_as_strings):
    database_records = list()
    for i in range(len(database_records_as_strings)):
        database_records.append(database_records_as_strings[i].split(','))
    Repository.repo.create_tables()
    Repository.repo.store(database_records)
    pass


def manage_orders(orders):
    for i in range(orders.count):
        record = orders[i].split(',')
        if record.count == 2:
            Repository.repo.send_shipment(record[0], record[1])
        elif record.count == 3:
            Repository.repo.receive_shipment(record[0], record[1], record[2])

def main(config_file, orders_file, output_file):
    with open(config_file,"r") as cfile:
        lines = cfile.readlines()
        database_building(lines)
    with open(orders_file,"r") as ofile:
        lines = ofile.readlines()
        manage_orders(lines)
    pass

if __name__ == '__main__':
    main("config.txt", "orders.txt", "")
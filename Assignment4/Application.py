# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import sys
from PersistenceLayer.DAO.vaccine_DAO import vaccine_DAO
from PersistenceLayer.DAO.supplier_DAO import supplier_DAO
from PersistenceLayer.DAO.clinic_DAO import clinic_DAO
from PersistenceLayer.DAO.logistic_DAO import logistic_DAO

from PersistenceLayer.DTO import vaccine_DTO, supplier_DTO, clinic_DTO, logistic_DTO
from PersistenceLayer.Repository import repo

def database_building(database_records):
    repo.create_tables()
    i = 1
    x = database_records[0][0]
    for number_of_vaccines in range(x):
        record = database_records[i]
        vaccine = vaccine_DTO(record[0], record[1], record[2], record[3])
        vaccine_DAO.insert(vaccine)
        i+=1
    x = x + database_records[0][1]            
    for number_of_suppliers in range(x):
        record = database_records[i]
        supplier = supplier_DTO(record[0], record[1], record[2])
        supplier_DAO.insert(supplier)
        i+=1
    x = x + database_records[0][2]
    for number_of_clinics in range(x):
        record = database_records[i]
        clinic = clinic_DTO(record[0], record[1], record[2], record[3])
        clinic_DAO.insert(clinic)
        i+=1
    x = x + database_records[0][3]
    for number_of_logistics in range(x):
        record = database_records[i]
        logistic = logistic_DTO(record[0], record[1], record[2], record[3])
        logistic_DAO.insert(logistic)
        i+=1
        pass

def reporting():
    pass

def manage_orders(orders):
    for i in range(orders.count):
        record = orders[i]
        if record.count == 2:
            repo.send_shipment(record[0], record[1])
        elif record.count == 3:
            repo.receive_shipment(record[0], record[1], record[2])

def main(config_file, orders_file, output_file):
    with open(config_file) as cfile:
        lines = cfile.readlines()
        database_building(lines)
    with open(orders_file) as ofile:
        lines = ofile.readlines()
        manage_orders(lines)
    pass

if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2], sys.argv[3])
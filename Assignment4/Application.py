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

def create_connection():
    pass

def reporting():
    pass

def read_orders_from_file():
    pass

def send_shipment(location, amount):
    pass

def receive_shipment(name, amount, date):
   # vaccine_controller = 
    #vaccine_controller.insert(name)
    pass

def main(config_file, orders_file, output_file):
    with open(config_file) as file:
        lines = file.readlines()
        database_building(lines)
        

    pass

if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2], sys.argv[3])
# -*- coding: utf-8 -*-
"""
Created on Mon Jan 11 15:14:17 2021

@author: luee
"""
import sqlite3
import atexit
from DAO.vaccine_DAO import vaccine_DAO
from DAO.supplier_DAO import supplier_DAO
from DAO.clinic_DAO import clinic_DAO
from DAO.logistic_DAO import logistic_DAO
from DTO import vaccine_DTO, supplier_DTO, clinic_DTO, logistic_DTO

class _Repository:
    
    def __init__(self):
        self._conn = sqlite3.connect('database.db')
        pass
    
    def get_connection(self):
        return self._conn
    
    def _close(self):
        self._conn.commit()
        self._conn.close()
        
    
    def create_tables(self):
        try:
            self._conn.executescript("""        
            
            CREATE TABLE logistics (
                id                 INT     PRIMARY KEY,
                name     TEXT    NOT NULL,
                count_sent  INT     NOT NULL,
                count_received  INT  NOT NULL
            );
            
            CREATE TABLE suppliers (
                id                 INT     PRIMARY KEY,
                name     TEXT    NOT NULL UNIQUE,
                logistic   INT     NOT NULL,
                FOREIGN KEY(logistic)     REFERENCES logistics(id)
            );
     
            CREATE TABLE clinics (
                id      INT     PRIMARY KEY,
                location  TEXT     NOT NULL UNIQUE,
                demand           INT     NOT NULL,
                logistic   INT     NOT NULL,
                FOREIGN KEY(logistic)     REFERENCES logistics(id)
            );
            
            CREATE TABLE vaccines (
                id      INT,
                date    DATETIME        NOT NULL,
                supplier    INT,
                quantity    INT     NOT NULL,
                FOREIGN KEY(supplier)     REFERENCES suppliers(id),
                PRIMARY KEY("id" AUTOINCREMENT)
            );
        """)
            #self._conn.commit()
        except Exception as error:
            print(error) 
            pass
        pass
    
    def store(database_records):
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
    
    
    def send_shipment(self, location, amount):
        #
        try:
           clinic_DAO.update_demand(location)
           #remove the amount from the vaccines table due to it's old date
           # I have to add a trigger on the case of ZERO in vaccine table.
                      
           temp = amount
           while(temp >0):
               vaccine = vaccine_DAO.get_older_vaccine()
               temp = vaccine_DAO.update_amount_and_process(vaccine, temp)
               supplier = supplier_DAO.get_supplier_by_name(vaccine.get_supplier())
               logistic = supplier.get_logistic()
               logistic_DAO.update_count_sent(logistic, amount)
            #add line to report(summary file)...
            
        except Exception as error:
            print(error)
        raise Exception('add line to report(summary file)...')
        
    def receive_shipment(self, name, amount, date):
        try:
            vaccine = vaccine_DTO(date, name, amount)
            vaccine_DAO.insert(vaccine)
            supplier = supplier_DAO.get_supplier_by_name(name)
            logistic = supplier.get_logistic()
            logistic_DAO.update_count_received(logistic, amount)
            
            #add line to report(summary file)...
            
            pass
        except Exception as error:
            print(error)
        raise Exception('add line to report(summary file)...')
        
# the repository singleton
repo = _Repository()
atexit.register(repo._close)
    
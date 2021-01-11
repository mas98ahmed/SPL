# -*- coding: utf-8 -*-
"""
Created on Mon Jan 11 15:14:17 2021

@author: luee
"""
import sqlite3
import atexit

class _Repository:

    def __init__(self):
        self._conn = sqlite3.connect('database.db')
        
 
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
                name     TEXT    NOT NULL,
                logistic   INT     NOT NULL,
                FOREIGN KEY(logistic)     REFERENCES logistics(id)
            );
     
            CREATE TABLE clinics (
                id      INT     PRIMARY KEY,
                location  TEXT     NOT NULL,
                demand           INT     NOT NULL,
                logistic   INT     NOT NULL,
                FOREIGN KEY(logistic)     REFERENCES logistics(id)
            );
            
            CREATE TABLE vaccines (
                id      INT         PRIMARY KEY,
                date    DATETIME        NOT NULL,
                supplier    INT,
                quantity    INT     NOT NULL,
                FOREIGN KEY(supplier)     REFERENCES suppliers(id)
            );
        """)
            
        except Exception as error:
            print(error) 
        
        
# the repository singleton
repo = _Repository()
atexit.register(repo._close)
    
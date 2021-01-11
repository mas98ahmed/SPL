# -*- coding: utf-8 -*-
"""
Created on Mon Jan 11 13:27:55 2021

@author: luee
"""
from PersistenceLayer.Repository import repo
class _clinic_DAO:
    def __init__(self):
        self._conn = repo._conn
    
    def insert(self, clinic):
        try:
            self._conn.execute("""
                INSERT INTO clinics (id, location, demand, logistic) VALUES (?, ?, ?, ?)
            """, [clinic.id, clinic.name, clinic.demand, clinic.logistic])
        except Exception as error:
            print(error)
            
    def update_demand(self, location, amount):  # should support it with some triggers before and after about the case of ZERO
        try:
            self._conn.execute(""" 
                UPDATE clinics
                SET demand = demand - ? 
                WHERE location = ?                               
            
            """, location, amount)
        except Exception as error:
            print(error)
            
            
clinic_DAO = _clinic_DAO()
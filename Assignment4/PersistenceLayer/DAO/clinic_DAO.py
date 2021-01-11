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
            
    def update_demand(self, _id, ,location, new_demand): # need to check about the location or id >>>>?????
        try:
            pass
        except Exception as error:
            print(error)
            
            
clinic_DAO = _clinic_DAO()
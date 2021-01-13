# -*- coding: utf-8 -*-
"""
Created on Mon Jan 11 13:27:55 2021

@author: luee
"""
import clinic_DTO
class _clinic_DAO:
    def __init__(self, conn):
        self._conn = conn


    def insert(self, clinic):
        try:
            self._conn.execute("""
                INSERT INTO clinics (id, location, demand, logistic) VALUES (?, ?, ?, ?);
            """, [clinic.get_id(), clinic.get_location(), clinic.get_demand(), clinic.get_logistic()])
            self._conn.commit()
        except Exception as error:
            print(error)

    
    def update_demand(self, location, amount):  # should support it with some triggers before and after about the case of ZERO
        try:
            self._conn.execute(""" 
                UPDATE clinics
                SET demand = demand - ? 
                WHERE location = ?                               
           ; """, [location, amount])
            self._conn.commit()
        except Exception as error:
            print(error)
            
            
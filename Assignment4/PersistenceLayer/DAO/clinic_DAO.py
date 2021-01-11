# -*- coding: utf-8 -*-
"""
Created on Mon Jan 11 13:27:55 2021

@author: luee
"""

class _clinic_DAO:
    def __init__(self, conn):
        self._conn = conn
    pass
    def insert(self, clinic):
        try:
            self._conn.execute("""
                INSERT INTO clinics (id, location, demand, logistic) VALUES (?, ?, ?, ?)
            """, [clinic.id, clinic.name, clinic.demand, clinic.logistic])
        except Exception as error:
            print(error)
clinic_DAO = _clinic_DAO()
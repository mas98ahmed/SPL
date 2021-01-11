# -*- coding: utf-8 -*-
"""
Created on Mon Jan 11 13:27:16 2021

@author: luee
"""
from PersistenceLayer.Repository import repo
class _vaccine_DAO:

    def __init__(self, conn):
        self._conn = repo._conn
    
    def insert(self, vaccine):
        try:
            self._conn.execute("""
                INSERT INTO vaccines (id, date, supplier, quantity) VALUES (?, ?, ?, ?)
            """, [vaccine.id, vaccine.date, vaccine.supplier, vaccine.quantity])
        except Exception as error:
            print(error)
    
    def update(self, vaccine):
        pass
    
vaccine_DAO = _vaccine_DAO()
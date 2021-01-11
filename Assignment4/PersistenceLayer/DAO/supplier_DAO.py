# -*- coding: utf-8 -*-
"""
Created on Mon Jan 11 13:27:55 2021

@author: luee
"""
from PersistenceLayer.Repository import repo
class _supplier_DAO:
    
    def __init__(self):
        self._conn = repo._conn
    
    def insert(self, supplier):
        try:
            self._conn.execute("""
                INSERT INTO suppliers (id, name, logistic) VALUES (?, ?, ?)
            """, [supplier.id, supplier.name, supplier.logistic])
        except Exception as error:
            print(error)
        
supplier_DAO = _supplier_DAO()
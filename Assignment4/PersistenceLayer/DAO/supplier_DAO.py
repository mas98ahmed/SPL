# -*- coding: utf-8 -*-
"""
Created on Mon Jan 11 13:27:55 2021

@author: luee
"""
from PersistenceLayer.Repository import repo
from PersistenceLayer.DTO import supplier_DTO
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
            
    def get_supplier_by_name(self, name):
        supplier = None
        try:
            cursor = self._conn.execute(""" SELECT * FROM suppliers WHERE name=? """,name)
            sup_row = cursor.fetchone()
            supplier = supplier_DTO(sup_row[0], sup_row[1], sup_row[2])
        except Exception as error:
            print(error)
        return supplier

        
supplier_DAO = _supplier_DAO()
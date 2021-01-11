# -*- coding: utf-8 -*-
"""
Created on Mon Jan 11 13:27:16 2021

@author: luee
"""
from PersistenceLayer.Repository import repo
class _vaccine_DAO:

    def __init__(self):
        self._conn = repo._conn
    
    def insert(self, vaccine):
        try:
            self._conn.execute("""
                INSERT INTO vaccines (id, date, supplier, quantity) VALUES (?, ?, ?, ?)
            """, [vaccine.id, vaccine.date, vaccine.supplier, vaccine.quantity])
        except Exception as error:
            print(error)
            
    def delete(self, _id):
        try:
            self._conn.execute(""" DELETE FROM vaccines where id=?""",_id)
            pass
        except Exception as error:
            print(error)
    
    def update(self, new_amount):
        try:
            pass
        except Exception as error:
            print(error)
            
    
    
vaccine_DAO = _vaccine_DAO()
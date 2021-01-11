# -*- coding: utf-8 -*-
"""
Created on Mon Jan 11 13:27:56 2021

@author: luee
"""
from PersistenceLayer.Repository import repo
from PersistenceLayer.DTO.logistic_DTO import logistic_DTO
class _logistic_DAO:
    def __init__(self):
        self._conn = repo.get_connection()
    
    def insert(self, logistic):
        try:
            self._conn.execute("""
            INSERT INTO logistics (id, name, count_sent, count_received) VALUES (?, ?, ?, ?)
            """, [logistic.get_id(), logistic.get_name(), logistic.get_count_sent(), logistic.get_count_received()]) 
        except Exception as error:
            print(error)
    
    def update_count_sent(self, _id, amount_to_add):
        try:
            self._conn.execute(""" UPDATE logistics SET count_sent=? where id=? """,[amount_to_add, _id])
            pass
        except Exception as error:
            print(error)
        
    def update_count_received(self, _id, amount_to_add):
        try:
            self._conn.execute(""" UPDATE logistics SET count_received=? where id=? """,[amount_to_add, _id])
            pass
        except Exception as error:
            print(error)
    
logistic_DAO = _logistic_DAO()
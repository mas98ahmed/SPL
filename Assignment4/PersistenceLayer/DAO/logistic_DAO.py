# -*- coding: utf-8 -*-
"""
Created on Mon Jan 11 13:27:56 2021

@author: luee
"""
from PersistenceLayer.Repository import repo
class _logistic_DAO:
    def __init__(self):
        self._conn = repo._conn
    
    def insert(self, logistic):
        try:
            self._conn.execute("""
            INSERT INTO logistics (id, name, count_sent, count_received) VALUES (?, ?, ?, ?)
            """, [logistic.id, logistic.name, logistic.count_sent, logistic.count_received]) 
        except Exception as error:
            print(error)
    
    def update_count_sent(self, _id, new_count_sent):
        try:
            self._conn.execute(""" UPDATE logistics SET count_sent=? where id=? """,[new_count_sent, _id])
            pass
        except Exception as error:
            print(error)
        
    def update_count_received(self, _id, new_count_received):
        try:
            self._conn.execute(""" UPDATE logistics SET count_received=? where id=? """,[new_count_received, _id])
            pass
        except Exception as error:
            print(error)
    
logistic_DAO = _logistic_DAO()
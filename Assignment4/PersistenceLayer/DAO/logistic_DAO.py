# -*- coding: utf-8 -*-
"""
Created on Mon Jan 11 13:27:56 2021

@author: luee
"""

class _logistic_DAO:
    def __init__(self, conn):
        self._conn = conn
    pass
    def insert(self, logistic):
        try:
            self._conn.execute("""
            INSERT INTO logistics (id, name, count_sent, count_received) VALUES (?, ?, ?, ?)
            """, [logistic.id, logistic.name, logistic.count_sent, logistic.count_received]) 
        except Exception as error:
            print(error)
        
logistic_DAO = _logistic_DAO()
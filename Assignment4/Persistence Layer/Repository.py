# -*- coding: utf-8 -*-
"""
Created on Mon Jan 11 15:14:17 2021

@author: luee
"""

class _Repository:
    def __init__(self, path):
        self._conn = sqlite3.connect('')
        self.students = _Students(self._conn)
        self.assignments = _Assignments(self._conn)
        self.grades = _Grades(self._conn)
 
    def _close(self):
        self._conn.commit()
        self._conn.close()
 
    def create_tables(self):
        _conn.executescript("""        
        
        CREATE TABLE logistics (
            id                 INT     PRIMARY KEY,
            name     TEXT    NOT NULL,
            count_sent  INT     NOT NULL,
            count_received  INT  NOT NULL
        );
        
        CREATE TABLE suppliers (
            id                 INT     PRIMARY KEY,
            name     TEXT    NOT NULL,
            logistic   INT     NOT NULL,
            FOREIGN KEY(logistic)     REFERENCES logistics(id)
        );
 
        CREATE TABLE clinics (
            id      INT     PRIMARY KEY,
            location  TEXT     NOT NULL,
            demand           INT     NOT NULL,
            logistic   INT     NOT NULL,
            FOREIGN KEY(logistic)     REFERENCES logistics(id)
        );
        
        CREATE TABLE vaccines (
            id      INT         PRIMARY KEY,
            date    DATETIME        NOT NULL,
            supplier    INT,
            quantity    INT     NOT NULL,
            FOREIGN KEY(supplier)     REFERENCES suppliers(id)
        );
    """)
 
# the repository singleton
repo = _Repository()
atexit.register(repo._close)
    
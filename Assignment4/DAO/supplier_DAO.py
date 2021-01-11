# -*- coding: utf-8 -*-
"""
Created on Mon Jan 11 13:27:55 2021

@author: luee
"""

class supplier_DAO:
    _id: int
    _name: str
    _logistic: int
    
    def __init__(self, _id, _name, _logistic):
        self._id = _id
        self._name = _name
        self._logistic = _logistic
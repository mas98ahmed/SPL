# -*- coding: utf-8 -*-
"""
Created on Mon Jan 11 13:27:55 2021

@author: luee
"""

class clinic_DTO:
    _id: int
    _location: str
    _demand: int
    _logistic: int
    def __init__(self, _id, _location, _demand, _logistic):
        self._id = _id
        self._location = _location
        self._demand = _demand
        self._logistic = _logistic
#!/usr/bin/env python
# -*- coding: utf-8 -*-
# $Id: Test.py 2981 2010-06-14 11:08:57Z Bear $
#
# Copyright (c) 2010 Nuwa Information Co., Ltd, All Rights Reserved.
#
# * CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License, Version 1.0 only
# (the "License").  You may not use this file except in compliance
# with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# * CDDL HEADER END
#
# $Author: Bear $
# $Date: 2010-06-14 19:08:57 +0800 (星期一, 14 六月 2010) $
# $Revision: 2981 $

import sys
import os

try:
    from Iuppiter.DistUtil import getExtensionPath
    sys.path.insert(0, getExtensionPath(base='..'))
except ImportError:
    pass

import PyLZJB

import string

s = string.letters * 50000

import unittest

class PyLZJBTest(unittest.TestCase):
    def test(self):
        c = PyLZJB.compress(s)
        print 'len(s): %ld, len(c): %ld' % (len(s), len(c))
        d = PyLZJB.decompress(c)
        
        self.assertEqual(d, s)

if __name__ == '__main__':
    unittest.main()

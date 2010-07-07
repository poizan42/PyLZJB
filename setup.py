#!/usr/bin/env python
# -*- coding: utf-8 -*-
# $Id: setup.py 3102 2010-07-07 05:58:50Z Bear $
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
# $Date: 2010-07-07 13:58:50 +0800 (星期三, 07 七月 2010) $
# $Revision: 3102 $

from distutils.core import setup

from Iuppiter import DistUtil

sitePackagesDir = DistUtil.getSitePackagesDir()

packages = []
dataFiles = [
    [sitePackagesDir, [DistUtil.getExtensionPath(module='PyLZJB')]],
]

setup(
    name='PyLZJB',
    description='Python binding for LZJB.',
    version='1.0',
    license='Common Development and Distribution License (CDDL)',
    author='Nuwa Information Co., Ltd.',
    author_email='bear@tracedig.com',
    url='http://www.tracedig.com/',
    #packages = packages,
    data_files = dataFiles,
)

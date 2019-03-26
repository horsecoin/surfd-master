from setuptools import setup

setup( name='surfdebugnode',
       version='0.1',
       description='A wrapper for launching and interacting with a Surf Debug Node',
       url='https://gitlab.com/surf.network/surfd',
       author='Surf, Inc.',
       author_email='hello@surf.io',
       license='See LICENSE.md',
       packages=['surfdebugnode'],
       #install_requires=['surfapi'],
       zip_safe=False )
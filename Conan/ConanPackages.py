import os, re

class ConanPackages:
    def __createFolderDownload (self, v_downloadsPath):
        print ('createFolderDownload')
        if not os.path.isdir(v_downloadsPath):
            os.mkdir(v_downloadsPath)
        os.chdir(v_downloadsPath)

    def __cloneRepo (self, v_name, v_downloadsPath, v_repoUrl):
        print ('cloneRepo')
        url = v_repoUrl + '/' + v_name + '.git'
        print ('url', url)
        if not os.path.isdir (v_downloadsPath):
            self.run('git clone ' + url)
        os.chdir(v_downloadsPath + '/' + v_name + '/Conan')

    def __createPackage (self, v_user, v_channel):
        print ('createPackage')
        self.run('conan create . ' + v_user + '/' + v_channel)
        
    def __parse (self, v_package):
        print ('parse')
        packageComponent = (re.split('[/@]', v_package, 3))
        return {'name' : packageComponent [0], 'version' : packageComponent [1], 'user' : packageComponent [2], 'channel' : packageComponent [3]}

    def GetPaths (self, v_packagesPath, v_packages):
        print ('GetPaths')
        includesPaths = []
        libsPaths     = []
        libsNames     = []

        for package in v_packages:
            packageComponent = ConanPackages.__parse (self, package)
            path             = v_packagesPath + '/' + packageComponent ['name'] + '/' + packageComponent ['version'] + '/' + packageComponent ['user'] + '/' + packageComponent ['channel'] + '/package'
            hashFolder       = os.listdir(path)
            includePath      = path + '/' + hashFolder [0] + '/include'
            libPath          = path + '/' + hashFolder [0] + '/lib'
            libName          = packageComponent ['name'] + 'Lib'

            if not os.path.isdir(includePath):
                raise Exception ('%s. Is not package include path', includePath)

            if not os.path.isdir(libPath):
                raise Exception ('%s. Is not package include lib path', libPath)

            includesPaths.append(includePath)
            libsPaths    .append(libPath)
            libsNames    .append(libName)

        return {'IncludesPaths' : includesPaths, 'LibsPaths' : libsPaths, 'LibsNames' : libsNames}

    def Install (self, v_downloadsPath, v_repoUrl, v_packages):
        print ('Install')
        for package in v_packages:
            packageComponent = ConanPackages.__parse (self, package)
            ConanPackages.__createFolderDownload (self, v_downloadsPath)
            ConanPackages.__cloneRepo            (self, packageComponent ['name'], v_downloadsPath, v_repoUrl)
            ConanPackages.__createPackage        (self, packageComponent ['user'], packageComponent ['channel'])

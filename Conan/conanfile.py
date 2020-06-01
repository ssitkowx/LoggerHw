from conans import ConanFile, CMake, tools
from ConanPackages import ConanPackages  
import os, re

class Conan(ConanFile):
    name            = "LoggerMock"
    version         = "1.0"
    user            = "ssitkowx"
    channel         = "stable"
    license         = "freeware"
    repoUrl         = "https://github.com/ssitkowx"
    url             = repoUrl + '/' + name + '.git'
    description     = "Logs informations in tests"
    settings        = "os", "compiler", "build_type", "arch"
    options         = {"shared": [True, False]}
    default_options = "shared=False"
    generators      = "cmake"
    author          = "sylsit"
    exports_sources = '../*'
    requires        = ["gtest/1.8.1@bincrafters/stable"]
    DownloadsPath   = "C:/Users/sitko/.conan/download"
    PackagesPath    = "C:/Users/sitko/.conan/data"
    Packages        = ["Logger/1.0@ssitkowx/stable"]

    def source (self):   
        ConanPackages.Install (self, self.DownloadsPath, self.repoUrl, self.Packages)

    def build (self):
        projectPath  = os.getcwd().replace('\Conan','')
        projectBuild = projectPath + '\\Build'
        
        if not os.path.exists(projectPath + '\\CMakeLists.txt'):
            projectPath  = self.downloadsPath + '\\' + self.name
            projectBuild = os.getcwd() + '\\Build'
            
        tools.replace_in_file(projectPath + "\\CMakeLists.txt", "Template", self.name, False)

        if self.settings.os == 'Windows' and self.settings.compiler == 'Visual Studio':
            packagesPaths = ConanPackages.GetPaths (self, self.PackagesPath, self.Packages)
            cmake = CMake(self)

            for packagePathKey, packagePathValue in packagesPaths.items ():
                cmake.definitions [packagePathKey] = packagePathValue

            cmake.configure(source_dir=projectPath, build_dir=projectBuild)
            cmake.build()
        else:
            raise Exception('Unsupported platform or compiler')
        
    def package (self):   
        projectPath = os.getcwd().replace('\Conan','')
        
        if not os.path.exists(projectPath + '\\CMakeLists.txt'):
            projectPath = self.downloadsPath + '\\' + self.name
    
        self.copy('*.h'     , dst='include', src= projectPath + '\\Project' , keep_path=False)
        self.copy('*.hxx'   , dst='include', src= projectPath + '\\Project' , keep_path=False)
        self.copy('*.lib'   , dst='lib'    , src= projectPath + '\Build\lib', keep_path=False)
        self.copy('*.dll'   , dst='bin'    , src= projectPath + '\Build\bin', keep_path=False)
        self.copy('*.dylib*', dst='lib'    , src= projectPath + '\Build\lib', keep_path=False)
        self.copy('*.so'    , dst='lib'    , src= projectPath + '\Build\lib', keep_path=False)
        self.copy('*.a'     , dst='lib'    , src= projectPath + '\Build\lib', keep_path=False)

    def package_info (self):
        self.cpp_info.libs = [self.name]
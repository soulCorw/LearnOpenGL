
Pod::Spec.new do |s|
    s.name         = 'SSKGL'
    s.version      = '1.0.0'
    s.summary      = 'SSK for Open GL'
    s.homepage     = 'https://github.com/soulCorw/LearnOpenGL'
    s.license      = { :type => "MIT", :file => "LICENSE" }
    s.authors      = {'Annieast42' => '1270086123soulcrow@gmail.com'}
    #s.platform     = :ios, '8.0'
    
    s.ios.deployment_target = "8.0"
    s.osx.deployment_target = "10.8"
    
    s.source       = {:git => 'git@github.com:soulCorw/LearnOpenGL.git', :tag => s.version}

    s.public_header_files = "Triangle/Triangle/include/*.h","Triangle/Triangle/include/GL/*.h"
    #s.source_files = 'include/**/*.{h,m}'
    #s.resource     = 'Sources/HBQRCode.bundle'
    #s.requires_arc = true

    s.vendored_libraries  = 'Triangle/Triangle/*.a'

    
end

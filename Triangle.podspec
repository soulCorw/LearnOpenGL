
Pod::Spec.new do |s|
    s.name         = 'SSKGL'
    s.version      = '1.0.0'
    s.summary      = 'SSK for Open GL'
    s.homepage     = 'https://github.com/soulCorw/LearnOpenGL'
    s.license      = 'MIT'
    s.authors      = {'Annieast42' => 'soulcrow@gitee.com'}
    s.platform     = :ios, '8.0'
    s.source       = {:git => 'git@github.com:soulCorw/LearnOpenGL.git', :tag => s.version}

    s.public_header_files = "include/*.h","Sources/Public/*.h"
    s.source_files = 'Sources/**/*.{h,m}'
    s.resource     = 'Sources/HBQRCode.bundle'
    s.requires_arc = true


    
end

#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html
#
Pod::Spec.new do |s|
  s.name             = 'IFStaticLib'
  s.version          = '0.0.1'
  s.summary          = 'TPM Paster Denpendency Lib.'
  s.description      = <<-DESC
TPM Paster Denpendency Lib.
                       DESC
  s.homepage         = 'https://github.com/kaisa695275735'
  s.license          = { :file => '../LICENSE' }
  s.author           = { 'Alibaba' => 'www.taobao.com' }
  s.source           = { :path => '.' }
  s.public_header_files = 'Header/*.h'
  s.vendored_libraries = "Lib/*.a"
  s.dependency 'Flutter'
  s.libraries = 'stdc++'
  s.requires_arc = true
  s.ios.deployment_target = '8.0'
end


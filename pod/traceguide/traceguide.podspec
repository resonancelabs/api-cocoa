Pod::Spec.new do |s|
  s.name             = "traceguide"
  s.version          = "0.1.0"
  s.summary          = "a cocoa / ObjC integration library for the Traceguide pilot."

  s.description      = <<-DESC
                       This space intentionally left blank.
                       DESC

  s.homepage         = "https://github.com/resonancelabs/api-cocoa"
  s.license          = 'MIT'
  s.author           = { "Ben Sigelman" => "bhs@resonancelabs.com" }
  s.source           = { :git => "https://github.com/resonancelabs/api-cocoa.git", :tag => s.version.to_s }

  s.platform     = :ios, '7.0'
  s.requires_arc = true

  s.source_files = 'Pod/Classes/**/*'
  s.resource_bundles = {
    'traceguide' => ['Pod/Assets/*.png']
  }

  # s.public_header_files = 'Pod/Classes/**/*.h'
  # s.frameworks = 'UIKit', 'MapKit'
  s.dependency 'thrift', '~> 0.9.2'
end
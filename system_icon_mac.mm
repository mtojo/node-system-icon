#include "system_icon.hpp"
#import <AppKit/AppKit.h>

std::vector<unsigned char> ImageToPng(NSImage* image)
{
  auto imageRef = [image CGImageForProposedRect:nil context:nil hints:nil];
  auto imageRep = [[NSBitmapImageRep alloc] initWithCGImage:imageRef];
  [imageRep setSize:[image size]];
  auto imageData =
    [imageRep representationUsingType:NSPNGFileType
                           properties:[[NSDictionary alloc] init]];
  auto p = static_cast<const unsigned char*>([imageData bytes]);
  return std::vector<unsigned char>{p, p + [imageData length]};
}

NSSize GetSize(IconSize size)
{
  switch (size)
  {
    case IconSize::ExtraSmall:
      return NSMakeSize(16, 16);
    case IconSize::Small:
      return NSMakeSize(32, 32);
    case IconSize::Medium:
      return NSMakeSize(128, 128);
    case IconSize::Large:
      return NSMakeSize(256, 256);
    case IconSize::ExtraLarge:
      return NSMakeSize(512, 512);
  }
}

template <>
void SystemIconAsyncWorker<ExtensionTag>::Execute()
{
  auto image = [[NSWorkspace sharedWorkspace]
    iconForFileType:[NSString stringWithUTF8String:this->name.c_str()]];
  [image setSize:GetSize(this->size)];

  if (image.valid)
  {
    this->result = ImageToPng(image);
  }
}

template <>
void SystemIconAsyncWorker<PathTag>::Execute()
{
  auto image = [[NSWorkspace sharedWorkspace]
    iconForFile:[NSString stringWithUTF8String:this->name.c_str()]];
  [image setSize:GetSize(this->size)];

  if (image.valid)
  {
    this->result = ImageToPng(image);
  }
}

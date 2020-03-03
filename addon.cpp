#include "system_icon.hpp"
#include <nan.h>

NAN_METHOD(getIconForExtension)
{
  if (info.Length() < 3)
  {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!info[0]->IsString() || !info[1]->IsNumber() || !info[2]->IsFunction())
  {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }

  Nan::Utf8String extension{info[0]};
  auto size = static_cast<IconSize>(info[1]->Int32Value(Nan::GetCurrentContext()).FromJust());
  auto callback = new Nan::Callback(info[2].As<v8::Function>());
  Nan::AsyncQueueWorker(
    new SystemIconAsyncWorker<ExtensionTag>(*extension, size, callback));
}

NAN_METHOD(getIconForPath)
{
  if (info.Length() < 3)
  {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!info[0]->IsString() || !info[1]->IsNumber() || !info[2]->IsFunction())
  {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }

  Nan::Utf8String path{info[0]};
  auto size = static_cast<IconSize>(info[1]->Int32Value(Nan::GetCurrentContext()).FromJust());
  auto callback = new Nan::Callback(info[2].As<v8::Function>());
  Nan::AsyncQueueWorker(
    new SystemIconAsyncWorker<PathTag>(*path, size, callback));
}

NAN_MODULE_INIT(init)
{
  NAN_EXPORT(target, getIconForExtension);
  NAN_EXPORT(target, getIconForPath);

  Nan::Set(target, Nan::New("ICON_SIZE_EXTRA_SMALL").ToLocalChecked(),
           Nan::New(static_cast<int>(IconSize::ExtraSmall)));
  Nan::Set(target, Nan::New("ICON_SIZE_SMALL").ToLocalChecked(),
           Nan::New(static_cast<int>(IconSize::Small)));
  Nan::Set(target, Nan::New("ICON_SIZE_MEDIUM").ToLocalChecked(),
           Nan::New(static_cast<int>(IconSize::Medium)));
  Nan::Set(target, Nan::New("ICON_SIZE_LARGE").ToLocalChecked(),
           Nan::New(static_cast<int>(IconSize::Large)));
  Nan::Set(target, Nan::New("ICON_SIZE_EXTRA_LARGE").ToLocalChecked(),
           Nan::New(static_cast<int>(IconSize::ExtraLarge)));
}

NODE_MODULE(system_icon, init);

#include <nan.h>
#include <string>

enum class IconSize
{
  ExtraSmall,
  Small,
  Medium,
  Large,
  ExtraLarge
};

struct ExtensionTag
{
};

struct PathTag
{
};

template <class Tag>
class SystemIconAsyncWorker : public Nan::AsyncWorker
{
public:
  SystemIconAsyncWorker(const char* name, IconSize size,
                        Nan::Callback* callback)
    : Nan::AsyncWorker{callback}, name{name}, size{size}
  {
  }

  void Execute() override;

protected:
  void HandleOKCallback() override
  {
    if (!this->result.empty())
    {
      v8::Local<v8::Value> argv[] = {
        Nan::Null(),
        Nan::CopyBuffer(
          static_cast<char*>(static_cast<void*>(this->result.data())),
          this->result.size())
          .ToLocalChecked(),
      };
      callback->Call(2, argv);
    }
    else
    {
      v8::Local<v8::Value> argv[] = {Nan::Error("Failed to load icon")};
      callback->Call(1, argv);
    }
  }

private:
  std::string name;
  IconSize size;
  std::vector<unsigned char> result;
};

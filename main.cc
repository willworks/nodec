#include <node.h>

namespace main {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Number;
using v8::Array;
using v8::Boolean;
using v8::Value;
using v8::Handle;
using v8::HandleScope;

void Method(const FunctionCallbackInfo<Value> &args){
    Isolate * isolate = args.GetIsolate();
    if (args[0]->IsNumber()){
        double a = args[0]->NumberValue();
        Local<Number> return_val =  Number::New(isolate,a+1);
        args.GetReturnValue().Set(return_val);
    };
    if (args[0]->IsBoolean()){
        bool a = args[0]->BooleanValue();
        Local<Boolean> return_val = Boolean::New(isolate,!a);
        args.GetReturnValue().Set(return_val);
    };
    if (args[0]->IsString()){
        Local<String> add_str = String::NewFromUtf8(isolate,"node");
        add_str = String::Concat(args[0]->ToString(),add_str);
        args.GetReturnValue().Set(add_str);
    };
}

//Handle<Value> ARRAY(const Arguments& args){
//    HandleScope scope;
//    int row_index;
//    Local<Array> dataArray=Array::New(10);      //dataArray=args[0].AsArray;
//    for(row_index=0;row_index<10;row_index++)
//    {
//        Local<Value> cell=Number::New(args[row_index]->NumberValue()+1);
//        dataArray->Set(Integer::New(row_index),cell);
//    }
//    return scope.Close(dataArray);
//}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "main", Method);
//  NODE_SET_METHOD(exports, "array", ARRAY);
}

NODE_MODULE(addon, init)

}  // namespace main
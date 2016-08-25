#include <node.h>

namespace main {

    using v8::Isolate;
    using v8::Local;
    using v8::Object;
    using v8::String;
    using v8::Number;
    using v8::Array;
    using v8::Boolean;
    using v8::Value;
    using v8::Integer;
    using v8::Handle;
    using v8::HandleScope;
    using v8::Function;
    using v8::FunctionCallback;
    using v8::FunctionCallbackInfo;

    void VAR(const FunctionCallbackInfo<Value> &args){
        // Get the default Isolate created at startup.
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

    // 给我们的对象附加一个函数
    void cb(const FunctionCallbackInfo<Value> &args){
        printf("this is called in addon module!\n");
    }

    void OBJ(const FunctionCallbackInfo<Value> &args){
        // Get the default Isolate created at startup.
        Isolate * isolate = args.GetIsolate();
        // 需要返回的v8对象
        Local<Object> v8Obj = Object::New(isolate);
        // 取得函数的指针
        FunctionCallback out_cb = cb;

        // 给v8对象设置一个键名为key值为111的字段
        v8Obj->Set(String::NewFromUtf8(isolate,"key"),Integer::New(isolate,111));
        // 给v8对象设置一个键名为run_cplus_fn的函数
        // v8Obj->Set(String::NewFromUtf8(isolate,"run_cplus_fn"),out_cb);

        // 如果传递的参数是v8::Object类型，再给对象设置一个键名为js_obj_keys的数组，数组值为js对象的key集合
        if(args[0]->IsObject()){
            Local<Object>  received_v8_obj = args[0]->ToObject();
            Local<Array> keys = received_v8_obj->GetOwnPropertyNames();
            v8Obj->Set(String::NewFromUtf8(isolate,"js_obj_keys"),keys);
        }
        args.GetReturnValue().Set(v8Obj);
    }

    void ARR(const FunctionCallbackInfo<Value> &args){
        Isolate* isolate = args.GetIsolate();
        Local<Array>tArr = Local<Array>::Cast(args[0]);
        args.GetReturnValue().Set(tArr->Get(0)->NumberValue());
    }

    void FUNC(const FunctionCallbackInfo<Value> &args){
        // Get the default Isolate created at startup.
        Isolate * isolate = args.GetIsolate();

        if(args[0]->IsFunction()){
            Local<Function> js_fn = Local<Function>::Cast(args[0]);
            for(int i=0;i<11;i++){
                printf("%d\n", i);
            }
            js_fn->Call(Null(isolate),0,NULL);
            args.GetReturnValue().Set(js_fn);
        }
    }

    void init(Local<Object> exports) {
      NODE_SET_METHOD(exports, "var", VAR);
      NODE_SET_METHOD(exports, "obj", OBJ);
      NODE_SET_METHOD(exports, "arr", ARR);
      NODE_SET_METHOD(exports, "func", FUNC);
    }

    NODE_MODULE(addon, init)

}  // namespace main
<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Login;
use App\Signin;
use App\Register;
use Session;
use App\User_log;

class SignupController extends Controller
{
    public function insert(Request $request)
    {
        return $request;
       $insert =  Login::create([
            'username'=>$request->username,
            'serialnumber'=>$request->number,
            'gender'=>$request->gender,
            'email'=>$request->email,
            'fingerprint_id'=>$request->fingerid,
            'fingerprint_select'=>0
        ]);

        if($insert){
            return "success";
        }
    }
    public function getId(Request $request)
    {
        session()->put('finger_id', $request->fingerid);
        return view('register')->with('title',"Register");
    }
    public function getdata(Request $request)
    {
        //return "Hello";
        if($request->Get_Fingerid == "get_id"){
           $reg = Register::all()->where('finger_status' , 1)->first();
           if($reg){
               $reg->finger_status = 2;
               $reg->save();
               return "add-id".$reg->id;
           }
           else{
               return "Nothing";
           }
        }
        if($request->confirm_id){
            $fingerid = $request->confirm_id;
            $reg = Register::all()->where('finger_status' , 2)->first();
            if($reg){
                $reg->finger_status = 3;
                $reg->save();
                return "FingerPrint has been added";
            }
        }
        if($request->FingerID){
            $fingerid = $request->FingerID;
            $reg = Register::find($fingerid);
            if($reg && $reg->finger_status == 3){
                $insert =  User_log::create([
                    'username'=>$reg->name,
                    'citizen_id'=>$reg->citizen_id,
                    'fingerprint_id'=>$request->FingerID
                ]);
                //return redirect('/home');
            }
            else{
                return "you are not found";
            }
        } 
        if($request->DeleteID){
            if($request->DeleteID == "check"){
                return "Nothing";
            }
        }
        //return "helllo";
       //return $request->FingerID;
        //$verify = Signin::all()->where('fingerprint_id', $request->FingerID)->first();
        //return $verify;
        // if ($verify == null) {
        //     return "Invalid User";
        // }
        // else{
            //return $verify;
            // $insert =  User_log::create([
            //     'username'=>"abcd",
            //     'serialnumber'=>1234,
            //     'fingerprint_id'=>$request->FingerID
            // ]);
            // return "user logged successful";
        }
}

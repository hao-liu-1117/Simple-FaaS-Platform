package main

import (
	"context"
	"flag"
	"fmt"
	"google.golang.org/grpc"

	"github.com/golang/protobuf/ptypes"
	faz "github.com/hao-liu-1117/csci499_hao-liu-1117/src/proto/faz"
	caw "github.com/hao-liu-1117/csci499_hao-liu-1117/src/proto/caw"
)

func Hook(client faz.FazServiceClient, e_type int32, e_func string) bool {
	req := &faz.HookRequest{EventType: e_type, EventFunction: e_func}
	_, err := client.Hook(context.Background(), req)
	if err != nil {
		return false
	}
	return true
}

func Unhook(client faz.FazServiceClient, e_type int32) bool {
	req := &faz.UnhookRequest{EventType: e_type}
	_, err := client.Unhook(context.Background(), req)
	if err != nil {
		return false
	}
	return true
}

func Event(client faz.FazServiceClient, req *faz.EventRequest) *faz.EventReply {
	rep, err := client.Event(context.Background(), req)
	if err != nil {
		return nil
	}
	return rep
}

func IsRegistered(client faz.FazServiceClient, e_func string) int32 {
	req := &faz.IsRegisteredRequest{EventFunction: e_func}
	rep, _ := client.IsRegistered(context.Background(), req)
	return rep.EventType
}

func RegisterHandler(client faz.FazServiceClient, username string) {
	// Check if username is empty.
	if len(username) == 0 {
		fmt.Println("Username can not be empty when register user.")
		return
	}
	// Construct caw::RegisteruserRequest.
	req := &caw.RegisteruserRequest{Username: username}
	rep := new(caw.RegisteruserRequest)

	// Pack to faz::EventRequest.
	var event_req faz.EventRequest
	event_req.EventType = IsRegistered(client, "registeruser")

	event_req.Payload, _ = ptypes.MarshalAny(req)
	event_rep := Event(client, &event_req)
	ptypes.UnmarshalAny(event_rep.Payload, rep)

	if len(rep.Username) == 0 {
		fmt.Println("Register user ", username, "failed")
		return
	}
	fmt.Println("Register user ", username, "success")
}

func PrintCaw(c *caw.Caw) {
	fmt.Println()
	fmt.Println("Caw username: ", c.Username)
	fmt.Println("Text: ", c.Text)
	fmt.Println("Id: ", string(c.Id))
	if len(c.ParentId) != 0 {
		fmt.Println("Reply to caw id: ", string(c.ParentId))
	}
}

func CawHandler(client faz.FazServiceClient, username string, text string, reply_id string) {
	// Check if username is empty.
	if len(username) == 0 {
		fmt.Println("Log in before sending a caw.")
		return
	}
	// Check if text is empty.
	if len(text) == 0 {
		fmt.Println("Text can not be empty.")
		return
	}
	// Construct caw::CawRequest
	req := &caw.CawRequest{Username: username, Text: text, ParentId: []byte(reply_id)}
	rep := new(caw.Caw)

	// Pack to faz::EventRequest
	var event_req faz.EventRequest
	event_req.EventType = IsRegistered(client, "caw")

	event_req.Payload, _ = ptypes.MarshalAny(req)
	event_rep := Event(client, &event_req)
	ptypes.UnmarshalAny(event_rep.Payload, rep)

	if string(rep.Id)=="-1" {
		// Check if username is valid.
		fmt.Println("User does not exist.")
		return
	} else if string(rep.ParentId)=="-1" {
		// Check if parent id exists.
		fmt.Println("Parent caw id does not exist.")
		return
	} else {
		fmt.Println("Post a caw successfully.")
		PrintCaw(rep)
	}
	
}

func FollowHandler(client faz.FazServiceClient, username string, to_follow string) {
	if len(username) == 0 {
		fmt.Println("Log in before following someone.")
		return
	}
	if len(to_follow) == 0 {
		fmt.Println("Can not follow an empty username.")
		return
	}
	// Construct caw::FollowRequest
	req := &caw.FollowRequest{Username: username, ToFollow: to_follow}
	rep := new(caw.RegisteruserRequest)

	// Pack to faz::EventRequest
	var event_req faz.EventRequest
	event_req.EventType = IsRegistered(client, "follow")

	event_req.Payload, _ = ptypes.MarshalAny(req)
	event_rep := Event(client, &event_req)
	ptypes.UnmarshalAny(event_rep.Payload, rep)
	if len(rep.Username) == 0 {
		fmt.Println("Follow user ", to_follow, " failed.")
		return
	} else {
		fmt.Println("Follow user ", to_follow, " success.")
	}
}

func ReadHandler(client faz.FazServiceClient, caw_id string) {
	// Check if caw_id is empty.
	if len(caw_id) == 0 {
		fmt.Println("Caw Id can not be empty.")
		return
	}
	// Create caw::ReadRequest.
	req := &caw.ReadRequest{CawId: []byte(caw_id)}
	rep := new(caw.ReadReply)
	// Pack to faz::EventRequest.
	var event_req faz.EventRequest
	event_req.EventType = IsRegistered(client, "read")

	event_req.Payload, _ = ptypes.MarshalAny(req)
	event_rep := Event(client, &event_req)
	ptypes.UnmarshalAny(event_rep.Payload, rep)

	if len(rep.Caws) == 0 {
		fmt.Println("Caw Id: ", caw_id, " does not exist.")
		return
	}
	fmt.Println("Caw Thread ", caw_id, ": ")
	for _, c := range rep.Caws {
		PrintCaw(c)
	}
}

func PrintProfile(username string, rep *caw.ProfileReply) {
	fmt.Println(username, "'s followers: ")
	for _, followers := range rep.Followers {
		fmt.Print(followers + " ")
	}
	fmt.Println()
	fmt.Println(username, "'s following: ")
	for _, following := range rep.Following {
		fmt.Print(following + " ")
	}
	fmt.Println()
}

func ProfileHandler(client faz.FazServiceClient, username string) {
	// Check if username is empty.
	if len(username) == 0 {
		fmt.Println("Log in before viewing profile.")
		return
	}
	// Construct caw::ProfileRequest.
	req := &caw.ProfileRequest{Username: username}
	rep := new(caw.ProfileReply)
	// Pack to faz::EventRequest
	var event_req faz.EventRequest
	event_req.EventType = IsRegistered(client, "profile")

	event_req.Payload, _ = ptypes.MarshalAny(req)
	event_rep := Event(client, &event_req)
	ptypes.UnmarshalAny(event_rep.Payload, rep)
	PrintProfile(username, rep)
}

func main() {

	f_registeruser := flag.String("registeruser", "", "Register a user given a username.")
	f_user := flag.String("user", "", "Specify a user you are going to use.")
	f_caw := flag.String("caw", "", "Specify caw text you are going to post.")
	f_reply := flag.String("reply", "", "ndicates that the new caw is a reply to the given id.")
	f_follow := flag.String("follow", "", "Starts following the given username.")
	f_read := flag.String("read", "", "Reads the caw thread starting at the given id.")
	f_profile := flag.Bool("profile", false, "Gets the user’s profile of following and followers.")
	f_hook := flag.Int("hook", -1, "Specify event type id that will be hooked with event function.")
	f_unhook := flag.Int("unhook", -1, "Specify event type id that will be unhooked.")
	f_event_func := flag.String("event_function", "", "Specify event function.")

	flag.Parse()

	conn, err := grpc.Dial("localhost:50000", grpc.WithInsecure(), grpc.WithBlock())
	if err != nil {
		fmt.Println("failed to connect")
		return
	}
	defer conn.Close()
	c := faz.NewFazServiceClient(conn)
	Hook(c, 1, "registeruser")
	Hook(c, 2, "caw")
	Hook(c, 3, "follow")
	Hook(c, 4, "read")
	Hook(c, 5, "profile")

	// Each command should only execute one command.
	var cmd_count int = 0
	if *f_registeruser != "" {cmd_count++}
	if *f_caw != "" {cmd_count++}
	if *f_follow != "" {cmd_count++}
	if *f_read != "" {cmd_count++}
	if *f_profile {cmd_count++}
	if *f_hook != -1 {cmd_count++}
	if *f_unhook != -1 {cmd_count++}

	if cmd_count > 1 {
		fmt.Println("Command should only execute one command.")
		return
	}
	if cmd_count == 0 {
		fmt.Println("No executable command found.")
		return
	}
	// Execute command.
	if *f_registeruser != "" {RegisterHandler(c, *f_registeruser)}
	if *f_caw != "" {CawHandler(c, *f_user, *f_caw, *f_reply)}
	if *f_follow != "" {FollowHandler(c, *f_user, *f_follow)}
	if *f_read != "" {ReadHandler(c, *f_read)}
	if *f_profile {ProfileHandler(c, *f_user)}
	if *f_hook != -1 {Hook(c, int32(*f_hook), *f_event_func)}
	if *f_unhook != -1 {Unhook(c, int32(*f_unhook))}
}

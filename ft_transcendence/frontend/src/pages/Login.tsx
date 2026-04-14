import { Card, Button, Label, TextInput } from "flowbite-react";

export default function Login() {
  return (
    <div className="mx-auto max-w-md px-4 sm:px-6 lg:px-8 py-8">
      <Card>
        <h2 className="mb-4 text-xl font-bold">Login</h2>
        <form className="flex flex-col gap-4">
          <div>
            <Label htmlFor="email">Email</Label>
            <TextInput id="email" name="email" type="email" placeholder="you@example.com" required />
          </div>
          <div>
            <Label htmlFor="password">Password</Label>
            <TextInput id="password" name="password" type="password" placeholder="••••••••" required />
          </div>
          <Button type="submit" color="purple">Sign in</Button>
        </form>
      </Card>
    </div>
  );
}

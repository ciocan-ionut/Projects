interface ErrorMessageProps {
  error: string | null;
}

export function ErrorMessage({ error }: ErrorMessageProps) {
  if (!error) return null;
  
  return <p className="error-message" style={{ color: 'red' }}>{error}</p>;
}

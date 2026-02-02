# Changelog

All notable changes to this project will be documented in this file.

## [1.0.0] - 2026-02-03

### Added
- Initial release of TD Animation Plugin
- Fade In/Out animations with customizable duration
- Slide animations from 4 directions (Left, Right, Top, Bottom)
- Pulse effect with configurable pulse count
- Blink effect with configurable blink count
- 8 different easing functions (Linear, Ease In, Ease Out, Ease InOut, Bounce, Elastic, Back, Cubic)
- Thread-safe animation system running at 60 FPS
- Per-player animation support
- Control functions (Stop, StopAll, IsAnimating)

### Changed
- Migrated from Zexx SDK to udan11/samp-plugin-sdk
- Updated SDK includes and paths

### Technical
- C++17 standard compliance
- Multi-threaded animation engine
- STL-based state management
- Cross-platform support (Windows/Linux)

## [Unreleased]

### Planned Features
- Rotation animations
- Scale animations  
- Path-based animations
- Animation callbacks
- Animation queuing system
- Custom animation curves
